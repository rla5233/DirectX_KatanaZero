#pragma once

// 설명 : 흑백 효과
class UGrayScale : public UEffect
{
public:
	// constructor destructor
	UGrayScale();
	~UGrayScale();
	
	// delete Function
	UGrayScale(const UGrayScale& _Other) = delete;
	UGrayScale(UGrayScale&& _Other) noexcept = delete;
	UGrayScale& operator=(const UGrayScale& _Other) = delete;
	UGrayScale& operator=(UGrayScale&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};

