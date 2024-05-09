#include "PreCompile.h"
#include "AfterImageObject.h"

#include "AfterImage.h"

UAfterImageObject::UAfterImageObject()
{
}

UAfterImageObject::~UAfterImageObject()
{
}

void UAfterImageObject::CreateAfterImage(float _DeltaTime)
{
	if (0.0f < TimeCount || 0.0f == _DeltaTime)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	AAfterImage* NewAfterImage = TargetRenderer->GetWorld()->SpawnActor<AAfterImage>("AfterImage").get();
	NewAfterImage->SetActorLocation(TargetRenderer->GetWorldPosition());
	NewAfterImage->SetTimeWeight(UpdateTimeWeight);
	NewAfterImage->SetBodyInfo(TargetRenderer);
	NewAfterImage->SetActiveDelayTime(ActiveDelayTime);
	NewAfterImage->SetPlusColor(PlusColor);
	NewAfterImage->SetMulColor(MulColor);

	TimeCount = DelayTime;
}
