#include "PreCompile.h"
#include "ShakeImage.h"

#include "KZImage.h"

UShakeImage::UShakeImage()
{
}

UShakeImage::~UShakeImage()
{
}

void UShakeImage::SetShakeActive(bool _Value)
{
	IsShakeValue = _Value;

	if (false == IsShakeValue)
	{
		Image->SetPosition(RefPosition);
	}
}

void UShakeImage::ShakeUpdate(float _DeltaTime)
{
	if (true == IsShakeValue)
	{
		FVector NextPos = RefPosition;
		NextPos.X += UEngineRandom::MainRandom.RandomFloat(ShakeRange.Min_X, ShakeRange.Max_X);
		NextPos.Y += UEngineRandom::MainRandom.RandomFloat(ShakeRange.Min_Y, ShakeRange.Max_Y);
		Image->SetPosition(NextPos);
	}
}
