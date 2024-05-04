#pragma once

class UKZImage;

// 설명 : Lerp 기능
class ULerpImage
{
public:
	// constructor destructor
	ULerpImage();
	~ULerpImage();
	
	// delete Function
	ULerpImage(const ULerpImage& _Other) = delete;
	ULerpImage(ULerpImage&& _Other) noexcept = delete;
	ULerpImage& operator=(const ULerpImage& _Other) = delete;
	ULerpImage& operator=(ULerpImage&& _Other) noexcept = delete;

	inline void SetLerpMovePos(const FVector& _StartPos, const FVector& _TargetPos)
	{
		StartPos = _StartPos;
		TargetPos = _TargetPos;
		IsLerpMoveValue = true;
	}

	inline bool IsLerpMove() const
	{
		return IsLerpMoveValue;
	}

	void SetLerpTimeWeight(float _Value)
	{
		if (0.0f > _Value)
		{
			_Value = 0.01f;
		}

		TimeWeight = _Value;
	}

protected:
	inline void SetImage(UKZImage* _Image)
	{
		Image = _Image;
	}
	
	void LerpMoveUpdate(float _DeltaTime);


private:
	UKZImage* Image = nullptr;

	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float MoveTime = 0.0f;
	float TimeWeight = 1.0f;
	bool IsLerpMoveValue = false;
};

