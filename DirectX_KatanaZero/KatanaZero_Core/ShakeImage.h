#pragma once

class UKZImage;

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

protected:
	inline void SetImage(UKZImage* _Image)
	{
		Image = _Image;
	}

	void ShakeUpdate(float _DeltaTime);

private:
	UKZImage* Image = nullptr;

};

