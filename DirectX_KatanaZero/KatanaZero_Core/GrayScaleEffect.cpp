#include "PreCompile.h"
#include "GrayScaleEffect.h"

UGrayScaleEffect::UGrayScaleEffect()
{
}

UGrayScaleEffect::~UGrayScaleEffect()
{
}

void UGrayScaleEffect::Init()
{
	SetMaterial("GrayScale");

	CopyTarget = UEngineRenderTarget::Create();
	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, WinScale, FVector::Zero);
}

void UGrayScaleEffect::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();

	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");
	Render(0.0f);
}
