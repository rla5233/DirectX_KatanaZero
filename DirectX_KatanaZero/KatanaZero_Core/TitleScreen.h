#pragma once
#include <EngineCore/StateManager.h>
#include "LerpObject.h"

// 설명 : Title 화면
class ATitleScreen : public AActor, public ULerpObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ATitleScreen();
	~ATitleScreen();

	// delete Function
	ATitleScreen(const ATitleScreen& _Other) = delete;
	ATitleScreen(ATitleScreen&& _Other) noexcept = delete;
	ATitleScreen& operator=(const ATitleScreen& _Other) = delete;
	ATitleScreen& operator=(ATitleScreen&& _Other) noexcept = delete;

	void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SettingSprite();
	void SettingRenderOrder();
	void SettingTransform();

private:
	UStateManager State;

	void StateInit();

	void SetTitleEndAim();

	float TitleEndWeightTime = 0.01f;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* Fence = nullptr;
	USpriteRenderer* Plants = nullptr;
	USpriteRenderer* Grass = nullptr;
	USpriteRenderer* Black = nullptr;

	USpriteRenderer* Neon_Katana = nullptr;
	USpriteRenderer* Neon_ZER = nullptr;
	USpriteRenderer* Neon_O = nullptr;
};

