#pragma once

// 설명 : Fade 기능
class UFadeObject
{
public:
	// constrcuter destructer
	UFadeObject();
	~UFadeObject();

	// delete Function
	UFadeObject(const UFadeObject& _Other) = delete;
	UFadeObject(UFadeObject&& _Other) noexcept = delete;
	UFadeObject& operator=(const UFadeObject& _Other) = delete;
	UFadeObject& operator=(UFadeObject&& _Other) noexcept = delete;

	void SetFadeIn(float _Start = 0.0f, float _Target = 1.0f);
	void SetFadeOut(float _Start = 1.0f, float _Target = 0.0f);

	void FadeUpdate(float _DeltaTime, float _TimeWeight = 1.0f);

	inline bool IsFade() const
	{
		return IsFadeValue;
	}

protected:
	void SetImage(UImage* _Image)
	{
		Image = _Image;
	}

private:
	UImage* Image = nullptr;

	float StartFade = 0.0f;
	float TargetFade = 0.0f;
	float FadeTime = 0.0f;
	bool IsFadeValue = false;
};

