#include "PreCompile.h"
#include "WaveEffect.h"

UWaveEffect::UWaveEffect()
{
}

UWaveEffect::~UWaveEffect()
{
}

void UWaveEffect::Init()
{
	SetMaterial("Wave");

	CopyTarget = UEngineRenderTarget::Create();
	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, WinScale, FVector::Zero);
}

void UWaveEffect::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();

	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");
	Render(0.0f);
}