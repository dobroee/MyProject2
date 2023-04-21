#pragma once

#include "CoreMinimal.h"
#include "IPhotoLibrary.h"


class PHOTOLIBRARY_API AndroidPhotoLibrary : public IPhotoLibrary
{
	
public:
	AndroidPhotoLibrary();

	virtual void OpenGallery() override;

#if PLATFORM_ANDROID
public:
	static struct _JNIEnv *ENV;
#endif

};