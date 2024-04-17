#pragma once
#include "Widget.h"
#include "EngineEnums.h"
#include "EngineSprite.h"
#include "EngineStruct.h"
// Ό³Έν :
class UImage : public UWidget
{
	GENERATED_BODY(UWidget);

public:
	UImage();
	~UImage();

	// delete Function
	UImage(const UImage& _Other) = delete;
	UImage(UImage&& _Other) noexcept = delete;
	UImage& operator=(const UImage& _Other) = delete;
	UImage& operator=(UImage&& _Other) noexcept = delete;

protected:
	void MaterialSettingEnd() override;

private:
	ResultColorValue ColorData;
	FCuttingData CuttingDataValue;
};

