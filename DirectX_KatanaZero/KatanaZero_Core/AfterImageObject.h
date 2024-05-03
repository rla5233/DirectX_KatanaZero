#pragma once

// ���� : �ܻ� ȿ�� ������Ʈ
class UAfterImageObject
{
public:
	// constrcuter destructer
	UAfterImageObject();
	~UAfterImageObject();

	// delete Function
	UAfterImageObject(const UAfterImageObject& _Other) = delete;
	UAfterImageObject(UAfterImageObject&& _Other) noexcept = delete;
	UAfterImageObject& operator=(const UAfterImageObject& _Other) = delete;
	UAfterImageObject& operator=(UAfterImageObject&& _Other) noexcept = delete;

	void CreateAfterImage(float _DeltaTime);
	void SetAfterImageTimeWeight(float _TimeWeight)
	{
		UpdateTimeWeight = _TimeWeight;
	}

protected:
	void SetTargetRenderer(USpriteRenderer* _TargetRenderer)
	{
		TargetRenderer = _TargetRenderer;
	}

private:
	USpriteRenderer* TargetRenderer = nullptr;

	float DelayTime = 1.0f / 60.0f;
	float TimeCount = 0.0f;
	float UpdateTimeWeight = 1.0f;
};

