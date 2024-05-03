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
	void SetTimeWeight(float _TimeWeight)
	{
		TimeWeight = _TimeWeight;
	}

	void SetAlphaWeight(float _AlphaWeight)
	{
		AlphaWeight = _AlphaWeight;
	}

	void SetColor(float4 _Color)
	{
		Color = _Color;	
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	USpriteRenderer* Body = nullptr;

	float4 Color = { 0.0f, 0.0f, 0.0f, 1.0f };
	float AlphaWeight = 0.0f;
	float TimeWeight = 1.0f;
};

