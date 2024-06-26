#include "PreCompile.h"
#include "LerpImage.h"

#include "KZImage.h"

ULerpImage::ULerpImage()
{
}

ULerpImage::~ULerpImage()
{
}

void ULerpImage::LerpMoveUpdate(float _DeltaTime)
{
	if (true == IsLerpMoveValue)
	{
		MoveTime += _DeltaTime * TimeWeight;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		Image->SetPosition(NextPos);

		Image->SetShakeRefPosition(NextPos);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsLerpMoveValue = false;
		}
	}
}
