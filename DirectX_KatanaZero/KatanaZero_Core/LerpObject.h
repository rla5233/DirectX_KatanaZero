#pragma once

// Ό³Έν :
class LerpObject
{
public:
	// constrcuter destructer
	LerpObject();
	~LerpObject();

	// delete Function
	LerpObject(const LerpObject& _Other) = delete;
	LerpObject(LerpObject&& _Other) noexcept = delete;
	LerpObject& operator=(const LerpObject& _Other) = delete;
	LerpObject& operator=(LerpObject&& _Other) noexcept = delete;

	FVector LerpMoveUpdate(float _DeltaTime, float _WeightTime = 1.0f);
	inline void SetLerpMovePos(const FVector& _StartPos, const FVector& _TargetPos)
	{
		StartPos = _StartPos;
		TargetPos = _TargetPos;
		IsMoveValue = true;
	}

	bool IsMove() const
	{
		return IsMoveValue;
	}

protected:

private:
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;
	bool IsMoveValue = false;
};

