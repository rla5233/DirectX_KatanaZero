#pragma once

// ���� : ��� ȿ��
class UGrayScaleEffect : public UEffect
{
public:
	// constructor destructor
	UGrayScaleEffect();
	~UGrayScaleEffect();
	
	// delete Function
	UGrayScaleEffect(const UGrayScaleEffect& _Other) = delete;
	UGrayScaleEffect(UGrayScaleEffect&& _Other) noexcept = delete;
	UGrayScaleEffect& operator=(const UGrayScaleEffect& _Other) = delete;
	UGrayScaleEffect& operator=(UGrayScaleEffect&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};

