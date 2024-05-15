#pragma once
#include <EngineCore/StateManager.h>

// Ό³Έν : EndingScreen
class AEndingScreen : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AEndingScreen();
	~AEndingScreen();
	
	// delete Function
	AEndingScreen(const AEndingScreen& _Other) = delete;
	AEndingScreen(AEndingScreen&& _Other) noexcept = delete;
	AEndingScreen& operator=(const AEndingScreen& _Other) = delete;
	AEndingScreen& operator=(AEndingScreen&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	void SetScreenMulColor(const float4& _MulColor);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* Smoke = nullptr;
	USpriteRenderer* Title = nullptr;
	std::vector<USpriteRenderer*> AllTide;
	const int TideNum = 8;

	bool IsFade = false;
	float AllMulColor = 1.0f;

	int EndingOrder = 0;

// FSM
private:
	UStateManager State;
	void StateInit();

	void EndingUpdate(float _DeltaTime);
	void EndingUpdate1(float _DeltaTime);

};

