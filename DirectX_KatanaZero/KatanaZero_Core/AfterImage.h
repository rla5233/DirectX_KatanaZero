#pragma once

// ¼³¸í : ÀÜ»ó È¿°ú ´ã´ç ¿¢ÅÍ
class AAfterImage : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AAfterImage();
	~AAfterImage();

	// delete Function
	AAfterImage(const AAfterImage& _Other) = delete;
	AAfterImage(AAfterImage&& _Other) noexcept = delete;
	AAfterImage& operator=(const AAfterImage& _Other) = delete;
	AAfterImage& operator=(AAfterImage&& _Other) noexcept = delete;

	void SetBodyInfo(USpriteRenderer* _Renderer);
	inline void SetTimeWeight(float _TimeWeight)
	{
		TimeWeight = _TimeWeight;
	}

	inline void SetPlusColor(float4 _Color)
	{
		PlusColor = _Color;
	}

	inline void SetMulColor(float4 _Color)
	{
		MulColor = _Color;
	}

	inline void SetActiveDelayTime(float _DelayTime)
	{
		ActiveDelayTime = _DelayTime;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	USpriteRenderer* Body = nullptr;

	float4 PlusColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 MulColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	float TimeWeight = 1.0f;
	float ActiveDelayTime = 0.0f;
};

