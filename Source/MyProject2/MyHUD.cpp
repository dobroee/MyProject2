// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "IImageWrapperModule.h"
#include "AndroidPhotoLibrary.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

#if PLATFORM_ANDROID
	PhotoLibrary = new AndroidPhotoLibrary();
#endif

}

void AMyHUD::OpenGallery()
{
	#if PLATFORM_ANDROID
	if (PhotoLibrary)
	{
		PhotoLibrary->OnImageSelected.BindUObject(this, &AMyHUD::OnImageSelected);
		PhotoLibrary->OpenGallery();
	}
	#endif
}

void AMyHUD::OnImageSelected(TArray<uint8> PhotoBytes)
{
	int32 len = PhotoBytes.Num();
	AsyncTask(ENamedThreads::GameThread, [=]()
		{
			//UTexture2D* ImportedTexture = LoadImageFromBytes(PhotoBytes);
			//BP_OnPhotoSelected(ImportedTexture);
		});

}

class UTexture2D* LoadImageFromBytes(const TArray<uint8>& ImageBytes)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(ImageBytes.GetData(), ImageBytes.Num());
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
	
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageBytes.GetData(), ImageBytes.Num()))
	{
		TArray<uint8> UncompressedBGRA;
		
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			FName UniqueName = MakeUniqueObjectName(nullptr, UTexture2D::StaticClass());
			UTexture2D* NewTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), EPixelFormat::PF_B8G8R8A8, UniqueName);
			
			if (!NewTexture) return nullptr;
			
			if (UTexture2D* ImageTexture = Cast<UTexture2D>(NewTexture))
			{
				void* TextureData = ImageTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memmove(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
				ImageTexture->PlatformData->Mips[0].BulkData.Unlock();
				ImageTexture->UpdateResource();
			}
			
			return NewTexture;
		}
	}
	
	return nullptr;

}