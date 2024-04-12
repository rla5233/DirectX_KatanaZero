#pragma once

// ���� : ��� Up_HUD
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

// �ʱ� Setting �Լ�
private:
	void SettingSprite();
	void SettingRenderOrder();
	void SettingTransform();

private:
	// BackGround
	USpriteRenderer* Bar = nullptr;

	// Mid
	USpriteRenderer* Timer = nullptr;
	USpriteRenderer* Timer_Bar = nullptr;
	
	// Left
	USpriteRenderer* Battery = nullptr;
	USpriteRenderer* Shift = nullptr;
	
	// Right
	USpriteRenderer* Weapon = nullptr;
	USpriteRenderer* KatanaIcon = nullptr;
	USpriteRenderer* ItemIcon = nullptr;
	USpriteRenderer* L_ClickIcon = nullptr;
	USpriteRenderer* R_ClickIcon = nullptr;
};

