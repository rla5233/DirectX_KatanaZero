#pragma once
#include <EngineCore/StateManager.h>

// Ό³Έν : EndingLevel 
class AEndingLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	AEndingLevel();
	~AEndingLevel();
	
	// delete Function
	AEndingLevel(const AEndingLevel& _Other) = delete;
	AEndingLevel(AEndingLevel&& _Other) noexcept = delete;
	AEndingLevel& operator=(const AEndingLevel& _Other) = delete;
	AEndingLevel& operator=(AEndingLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

// FSM
private:
	UStateManager State;
	void StateInit();

};

