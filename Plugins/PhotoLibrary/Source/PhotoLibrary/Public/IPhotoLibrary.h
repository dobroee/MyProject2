#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPhotoLibrary.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UPhotoLibrary : public UInterface
{
	GENERATED_BODY()
};

class IPhotoLibrary
{
	GENERATED_BODY()

public:
	virtual void OpenGallery() = 0;
};