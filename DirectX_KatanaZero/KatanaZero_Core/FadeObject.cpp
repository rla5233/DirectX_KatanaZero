#include "PreCompile.h"
#include "FadeObject.h"

UFadeObject::UFadeObject()
{
}

UFadeObject::~UFadeObject()
{
}

void UFadeObject::SetFadeIn(float _Start, float _Target)
{
	FadeTime = 0.0f;
	StartFade = _Start;
	TargetFade = _Target;
	IsFadeValue = true;
}

void UFadeObject::SetFadeOut(float _Start, float _Target)
{
	FadeTime = 0.0f;
	StartFade = _Start;
	TargetFade = _Target;
	IsFadeValue = true;
}

void UFadeObject::FadeUpdate(float _DeltaTime)
{
	if (true == IsFadeValue)
	{
		FadeTime += _DeltaTime;

		float NextAlpha = UContentsMath::LerpClampf(StartFade, TargetFade, FadeTime);
		Image->SetMulColor({ 1.0f, 1.0f, 1.0f, NextAlpha });

		if (1.0f < FadeTime)
		{
			IsFadeValue = false;
			FadeTime = 0.0f;
		}
	}
}
