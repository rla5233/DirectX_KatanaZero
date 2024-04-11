#pragma once

// 설명 : 선형보간(Lerp) 기능
class ULerpObject
{
public:
	// constrcuter destructer
	ULerpObject();
	~ULerpObject();

	// delete Function
	ULerpObject(const ULerpObject& _Other) = delete;
	ULerpObject(ULerpObject&& _Other) noexcept = delete;
	ULerpObject& operator=(const ULerpObject& _Other) = delete;
	ULerpObject& operator=(ULerpObject&& _Other) noexcept = delete;

	FVector LerpMoveUpdate(float _DeltaTime, float _WeightTime = 1.0f);
	inline void SetLerpMovePos(const FVector& _StartPos, const FVector& _TargetPos)
	{
		StartPos = _StartPos;
		TargetPos = _TargetPos;
		IsLerpMoveValue = true;
	}

	bool IsLerpMove() const
	{
		return IsLerpMoveValue;
	}

protected:

private:
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;
	bool IsLerpMoveValue = false;
};

