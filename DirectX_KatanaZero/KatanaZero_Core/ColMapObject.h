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

	// ColMap Setting
	void SetColMapSprite(std::string_view _Name, float _ScaleRatio, bool _AutoSize)
	{
		ColMap->SetAutoSize(_ScaleRatio, _AutoSize);
		SetColMapSprite(_Name);
	}

	void SetColMapSprite(std::string_view _Name)
	{
		ColMap->SetSprite(_Name);
		MapTex = UEngineTexture::FindRes(_Name);

		// Auto Location
		FVector SpriteScale = UEngineTexture::FindRes(_Name)->GetScale();
		ColMap->Transform.SetPosition({ SpriteScale.hX(), SpriteScale.hY(), 0.0f });
	}

	void SetColMapSpriteScale(const FVector& _Scale)
	{
		ColMap->Transform.SetScale(_Scale);
	}

	static std::shared_ptr<UEngineTexture> GetMapTex()
	{
		return MapTex;
	}

	// BackGround Setting
	void SetBGSprite(std::string_view _Name, float _ScaleRatio, bool _AutoSize)
	{
		BackGround->SetAutoSize(_ScaleRatio, _AutoSize);
		SetBGSprite(_Name);
	}

	void SetBGSprite(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);

		// Auto Location
		FVector SpriteScale = UEngineTexture::FindRes(_Name)->GetScale();
		BackGround->Transform.SetPosition({ SpriteScale.hX(), SpriteScale.hY(), 0.0f });
	}

	void SetBGSpriteScale(const FVector& _Scale)
	{
		BackGround->Transform.SetScale(_Scale);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void ActiveSwitchCheck();

private:
	static std::shared_ptr<UEngineTexture> MapTex;
	USpriteRenderer* ColMap = nullptr;
	USpriteRenderer* BackGround = nullptr;
};

