#pragma once

// 설명 : Fade 기능
class UFadeImage
{
public:
	// constrcuter destructer
	UFadeImage();
	~UFadeImage();

	// delete Function
	UFadeImage(const UFadeImage& _Other) = delete;
	UFadeImage(UFadeImage&& _Other) noexcept = delete;
	UFadeImage& operator=(const UFadeImage& _Other) = delete;
	UFadeImage& operator=(UFadeImage&& _Other) noexcept = delete;

	void SetFadeIn(float _Start = 0.0f, float _Target = 1.0f);
	void SetFadeOut(float _Start = 1.0f, float _Target = 0.0f);

	inline bool IsFade() const
	{
		return IsFadeValue;
	}

	void SetFadeTimeWeight(float _Value)
	{
		if (0.0f >= _Value)
		{
			MsgBoxAssert("잘못된 값을 설정하였습니다.")
			return;
		}

		TimeWeight = _Value;
	}

protected:
	inline void SetImage(UImage* _Image)
	{
		Image = _Image;
	}

	void FadeUpdate(float _DeltaTime);

private:
	UImage* Image = nullptr;

	float StartFade = 0.0f;
	float TargetFade = 0.0f;
	float FadeTime = 0.0f;
	float TimeWeight = 1.0f;
	bool IsFadeValue = false;
};

