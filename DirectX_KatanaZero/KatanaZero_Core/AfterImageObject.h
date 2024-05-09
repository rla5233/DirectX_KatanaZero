#pragma once

// 설명 : 잔상 효과 오브젝트
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

	inline void SetAfterImageTimeWeight(float _TimeWeight)
	{
		UpdateTimeWeight = _TimeWeight;
	}

	inline void SetAfterImagePlusColor(const float4& _Color)
	{
		PlusColor = _Color;
	}

	inline void SetAfterImageMulColor(const float4& _Color)
	{
		MulColor = _Color;
	}

	inline void SetAfterImageActiveDelayTime(float _DelayTime)
	{
		ActiveDelayTime = _DelayTime;
	}

	inline void SetAfterImageDelayTime(float _Time)
	{
		DelayTime = _Time;
	}

	void CreateAfterImage(float _DeltaTime);

protected:
	void SetTargetRenderer(USpriteRenderer* _TargetRenderer)
	{
		TargetRenderer = _TargetRenderer;
	}

private:
	USpriteRenderer* TargetRenderer = nullptr;

	float4 PlusColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	float DelayTime = 1.0f / 60.0f;
	float TimeCount = 0.0f;
	float UpdateTimeWeight = 1.0f;
	float ActiveDelayTime = 0.0f;
};

