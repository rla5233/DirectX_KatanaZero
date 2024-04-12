#pragma once

// 설명 : 상단 Up_HUD
class AUp_HUD : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AUp_HUD();
	~AUp_HUD();

	// delete Function
	AUp_HUD(const AUp_HUD& _Other) = delete;
	AUp_HUD(AUp_HUD&& _Other) noexcept = delete;
	AUp_HUD& operator=(const AUp_HUD& _Other) = delete;
	AUp_HUD& operator=(AUp_HUD&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SettingSprite();
	void SettingRenderOrder();
	void SettingTransform();

private:
	USpriteRenderer* Bar = nullptr;
	USpriteRenderer* Timer = nullptr;
	USpriteRenderer* Battery = nullptr;
	USpriteRenderer* Shift = nullptr;
	USpriteRenderer* Weapon = nullptr;
};

