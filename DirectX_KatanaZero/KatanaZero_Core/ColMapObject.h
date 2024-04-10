#pragma once

// Ό³Έν :
class AColMapObject : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AColMapObject();
	~AColMapObject();
	
	// delete Function
	AColMapObject(const AColMapObject& _Other) = delete;
	AColMapObject(AColMapObject&& _Other) noexcept = delete;
	AColMapObject& operator=(const AColMapObject& _Other) = delete;
	AColMapObject& operator=(AColMapObject&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name)
	{
		ColMap->SetSprite(_Name);
	}

	void SetSpriteScale(const FVector& _Scale)
	{
		ColMap->Transform.SetScale(_Scale);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* ColMap = nullptr;

};

