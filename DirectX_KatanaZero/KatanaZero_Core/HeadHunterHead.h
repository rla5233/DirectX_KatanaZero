#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"

// Ό³Έν : HeadHunter Head 
class AHeadHunterHead :
	public AActor,
	public UPhysicsObject,
	public UPixelColObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AHeadHunterHead();
	~AHeadHunterHead();

	// delete Function
	AHeadHunterHead(const AHeadHunterHead& _Other) = delete;
	AHeadHunterHead(AHeadHunterHead&& _Other) noexcept = delete;
	AHeadHunterHead& operator=(const AHeadHunterHead& _Other) = delete;
	AHeadHunterHead& operator=(AHeadHunterHead&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	USpriteRenderer* GetBody() const
	{
		return Body;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;

// FSM
private:
	UStateManager State;
	void StateInit();

};

