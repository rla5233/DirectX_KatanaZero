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

	inline void SetAfterImageAlphaWeight(float _AlphaWeight)
	{
		AlphaWeight = _AlphaWeight;
	}

	inline void SetAfterImagePlusColor(const float4& _Color)
	{
		Color = _Color;
	}

	void CreateAfterImage(float _DeltaTime);

protected:
	void SetTargetRenderer(USpriteRenderer* _TargetRenderer)
	{
		TargetRenderer = _TargetRenderer;
	}

private:
	USpriteRenderer* TargetRenderer = nullptr;

	float4 Color = { 0.0f, 0.0f, 0.0f, 1.0f };
	float DelayTime = 1.0f / 60.0f;
	float TimeCount = 0.0f;
	float UpdateTimeWeight = 1.0f;
	float AlphaWeight = 0.0f;
};

