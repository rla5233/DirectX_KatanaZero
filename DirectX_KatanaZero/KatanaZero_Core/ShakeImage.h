#pragma once

class UKZImage;

struct FShakeRange
{
	float Min_X = 0.0f;
	float Max_X = 0.0f;
	float Min_Y = 0.0f;
	float Max_Y = 0.0f;
};

// 설명 : 진동 효과
class UShakeImage
{
public:
	// constructor destructor
	UShakeImage();
	~UShakeImage();
	
	// delete Function
	UShakeImage(const UShakeImage& _Other) = delete;
	UShakeImage(UShakeImage&& _Other) noexcept = delete;
	UShakeImage& operator=(const UShakeImage& _Other) = delete;
	UShakeImage& operator=(UShakeImage&& _Other) noexcept = delete;

	inline void SetShakeRange(FShakeRange _Range)
	{
		ShakeRange = _Range;
	}

	inline void SetShakeRefPosition(const FVector& _Pos)
	{
		RefPosition = _Pos;
	}

	void SetShakeActive(bool _Value);

protected:
	inline void SetImage(UKZImage* _Image)
	{
		Image = _Image;
	}

	void ShakeUpdate(float _DeltaTime);

private:
	UKZImage* Image = nullptr;

	bool IsShakeValue = false;

	FShakeRange ShakeRange;
	FVector RefPosition = FVector::Zero;
};

