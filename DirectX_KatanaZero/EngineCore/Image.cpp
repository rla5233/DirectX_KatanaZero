#include "PreCompile.h"
#include "Image.h"

UImage::UImage()
{
	SetMesh("Rect");
	SetMaterial("2DImage");
}

UImage::~UImage()
{
}


void UImage::MaterialSettingEnd()
{
	Super::MaterialSettingEnd();
	Resources->SettingTexture("Image", "EngineBaseTexture.png", "POINT");
	Resources->SettingConstantBuffer("ResultColorValue", ColorData);
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);
}
