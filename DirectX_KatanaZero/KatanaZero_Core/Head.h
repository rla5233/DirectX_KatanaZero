#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"

// Ό³Έν : HeadHunter Head 
class AHead :
	public AActor,
	public UPhysicsObject,
	public UPixelColObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AHead();
	~AHead();

	// delete Function
	AHead(const AHead& _Other) = delete;
	AHead(AHead&& _Other) noexcept = delete;
	AHead& operator=(const AHead& _Other) = delete;
	AHead& operator=(AHead&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;
	
	UCollision* Test = nullptr;

// FSM
private:
	UStateManager State;
	void StateInit();

};

