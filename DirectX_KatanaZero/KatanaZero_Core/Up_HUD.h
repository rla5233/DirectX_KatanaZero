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

// 초기 Setting 함수
private:
	void CreateImage();
	void SettingImage();
	void SettingRenderOrder();
	void SettingTransform();

private:
	// BackGround
	UImage* Bar = nullptr;

	// Mid
	UImage* Timer = nullptr;
	UImage* Timer_Bar = nullptr;
	
	// Left
	UImage* Battery = nullptr;
	std::vector<UImage*> Battery_Part;
	UImage* Shift = nullptr;
	
	// Right
	UImage* Weapon = nullptr;
	UImage* KatanaIcon = nullptr;
	UImage* ItemIcon = nullptr;
	UImage* L_ClickIcon = nullptr;
	UImage* R_ClickIcon = nullptr;
};

