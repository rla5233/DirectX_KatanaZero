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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	USpriteRenderer* Body = nullptr;

	float Alpha = 1.0f;
	float TimeWeight = 1.0f;
};

