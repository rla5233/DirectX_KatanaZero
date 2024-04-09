#include "PreCompile.h"
#include "LerpObject.h"

LerpObject::LerpObject()
{
}

LerpObject::~LerpObject()
{
}

FVector LerpObject::LerpMoveUpdate(float _DeltaTime, float _WeightTime)
{
	if (true == IsMoveValue)
	{
		MoveTime += _DeltaTime * _WeightTime;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);

		if (1.0f <= MoveTime)
		{
			MoveTime = 0.0f;
			IsMoveValue = false;
		}

		return NextPos;
	}
}
