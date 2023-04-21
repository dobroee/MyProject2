// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Texture2D.h"
#include "IPhotoLibrary.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	class IPhotoLibrary* PhotoLibrary;
	
protected:
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable)
	void OpenGallery();

	void OnImageSelected(TArray<uint8> PhotoBytes);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnPhotoSelected(class UTexture2D* SelectedPhoto);
	
	//class UTexture2D* LoadImageFromBytes(const TArray<uint8>& ImageBytes);
};
