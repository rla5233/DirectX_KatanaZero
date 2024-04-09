#pragma once
#include "ContentsEnum.h"
#include "LerpObject.h"

// Ό³Έν :
class ATitleScreen : public AActor, public LerpObject
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

	void StateChange(ETitleState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	
private:
	void StateUpdate(float _DeltaTime);

private:
	void IntroStart();
	void Intro(float _DeltaTime);
	void IntroAnimation(float _DeltaTime);

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* Fence = nullptr;
	USpriteRenderer* Plants = nullptr;

	ETitleState State = ETitleState::None;
};

