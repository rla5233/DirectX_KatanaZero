#include "PreCompile.h"
#include "LerpObject.h"

ULerpObject::ULerpObject()
{
}

ULerpObject::~ULerpObject()
{
}

FVector ULerpObject::LerpMoveUpdate(float _DeltaTime, float _WeightTime)
{
	if (true == IsLerpMoveValue)
	{
		if (0.0f > _WeightTime)
		{
			_WeightTime = 0.01f;
		}

		MoveTime += _DeltaTime * _WeightTime;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsLerpMoveValue = false;
		}

		return NextPos;
	}

	return TargetPos;
}
