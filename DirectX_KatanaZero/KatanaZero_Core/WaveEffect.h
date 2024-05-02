#pragma once
#include "KZEffect.h"

// 설명 : Wave 효과
class UWaveEffect : public UKZEffect
{
public:
	// constrcuter destructer
	UWaveEffect();
	~UWaveEffect();

	// delete Function
	UWaveEffect(const UWaveEffect& _Other) = delete;
	UWaveEffect(UWaveEffect&& _Other) noexcept = delete;
	UWaveEffect& operator=(const UWaveEffect& _Other) = delete;
	UWaveEffect& operator=(UWaveEffect&& _Other) noexcept = delete;

	void SetEffectType(EWaveEffectType _WaveType)
	{
		SetTemp0(static_cast<float>(_WaveType));
	}

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};

