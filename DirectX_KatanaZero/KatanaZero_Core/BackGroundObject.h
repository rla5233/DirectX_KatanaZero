#pragma once

// 설명 : 배경(맵) 담당 오브젝트
class ABackGroundObject : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABackGroundObject();
	~ABackGroundObject();

	// delete Function
	ABackGroundObject(const ABackGroundObject& _Other) = delete;
	ABackGroundObject(ABackGroundObject&& _Other) noexcept = delete;
	ABackGroundObject& operator=(const ABackGroundObject& _Other) = delete;
	ABackGroundObject& operator=(ABackGroundObject&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetSpriteScale(const FVector& _Scale)
	{
		BackGround->Transform.SetScale(_Scale);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;

};

