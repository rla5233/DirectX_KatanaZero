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

	void SetSprite(std::string_view _Name, UINT _Index = 0);
	void SetSpriteInfo(const FSpriteInfo& _Info);
	void SetAutoSize(float _ScaleRatio, bool _AutoSize);
	void SetSamplering(ETextureSampling _Value);


protected:
	void MaterialSettingEnd() override;

private:
	bool AutoSize = false;
	float ScaleRatio = 1.0f;
	FSpriteInfo CurInfo;
	EPivot Pivot = EPivot::MAX;
	std::shared_ptr<UEngineTexture> CurTexture = nullptr;
	ETextureSampling SamplingValue = ETextureSampling::POINT;
	EEngineDir Dir = EEngineDir::MAX;

	FResultColorValue ColorData;
	FCuttingData CuttingDataValue;

};

