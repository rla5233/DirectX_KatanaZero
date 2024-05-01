#pragma once

// 설명 : Wave 효과
class UWaveEffect : public UEffect
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

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};

