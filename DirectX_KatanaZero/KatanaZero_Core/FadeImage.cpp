#include "PreCompile.h"
#include "FadeImage.h"

UFadeImage::UFadeImage()
{
}

UFadeImage::~UFadeImage()
{
}

void UFadeImage::SetFadeIn(float _Start, float _Target)
{
	FadeTime = 0.0f;
	StartFade = _Start;
	TargetFade = _Target;
	IsFadeValue = true;
}

void UFadeImage::SetFadeOut(float _Start, float _Target)
{
	FadeTime = 0.0f;
	StartFade = _Start;
	TargetFade = _Target;
	IsFadeValue = true;
}

void UFadeImage::FadeUpdate(float _DeltaTime)
{
	if (true == IsFadeValue)
	{
		FadeTime += TimeWeight * _DeltaTime;

		float NextAlpha = UContentsMath::LerpClampf(StartFade, TargetFade, FadeTime);
		Image->SetMulColor({ 1.0f, 1.0f, 1.0f, NextAlpha });

		if (1.0f < FadeTime)
		{
			IsFadeValue = false;
			FadeTime = 0.0f;
		}
	}
}
