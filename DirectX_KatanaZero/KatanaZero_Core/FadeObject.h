#pragma once

// ���� : Fade ���
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

	inline bool IsFade() const
	{
		return IsFadeValue;
	}

	inline void SetFadeTimeWeight(float _Value)
	{
		if (0.0f >= _Value)
		{
			MsgBoxAssert("�߸��� ���� �����Ͽ����ϴ�.")
			return;
		}

		TimeWeight = _Value;
	}

protected:
	void SetImage(UImage* _Image)
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

