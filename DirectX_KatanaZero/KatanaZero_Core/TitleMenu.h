#pragma once

// ���� : Title �޴�
class ATitleMenu : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ATitleMenu();
	~ATitleMenu();
	
	// delete Function
	ATitleMenu(const ATitleMenu& _Other) = delete;
	ATitleMenu(ATitleMenu&& _Other) noexcept = delete;
	ATitleMenu& operator=(const ATitleMenu& _Other) = delete;
	ATitleMenu& operator=(ATitleMenu&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SettingSprite();
	void SettingRenderOrder();
	void SettingTransform();

private:
	USpriteRenderer* Text = nullptr;
	USpriteRenderer* BlackBar = nullptr;
	USpriteRenderer* WhiteBar = nullptr;
};

