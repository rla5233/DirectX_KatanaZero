#pragma once

// 설명 : 충돌 맵 담당 클래스
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
		ColMap->SetPosition({ SpriteScale.hX(), SpriteScale.hY(), 0.0f });
	}

	inline void SetColMapSpriteScale(const FVector& _Scale)
	{
		ColMap->SetScale(_Scale);
	}

	inline std::shared_ptr<UEngineTexture> GetMapTex() const
	{
#ifdef _DEBUG
		if (nullptr == MapTex)
		{
			MsgBoxAssert("맵 택스처가 설정되지 않았습니다.")
		}
#endif // _DEBUG

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
		BackGround->SetPosition({ SpriteScale.hX(), SpriteScale.hY(), 0.0f });
	}

	inline void SetBGSpriteScale(const FVector& _Scale)
	{
		BackGround->SetScale(_Scale);
	}

	inline USpriteRenderer* GetBackGround() const
	{
		return BackGround;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void ActiveSwitchCheck();

private:
	std::shared_ptr<UEngineTexture> MapTex = nullptr;
	USpriteRenderer* ColMap = nullptr;
	USpriteRenderer* BackGround = nullptr;
};

