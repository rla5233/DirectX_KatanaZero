#pragma once

// ���� : �ܻ� ȿ�� ��� ����
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	USpriteRenderer* Body = nullptr;

	float4 Color = { 0.426f, 0.502f, 0.752f, 1.0f };
	float AlphaWeight = 0.0f;
	float TimeWeight = 1.0f;
};

