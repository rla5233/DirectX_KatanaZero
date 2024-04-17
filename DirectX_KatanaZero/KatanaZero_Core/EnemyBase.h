#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"

// Ό³Έν :
class AEnemyBase : public AActor, public UPixelColObject, public UPhysicsObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AEnemyBase();
	~AEnemyBase();

	// delete Function
	AEnemyBase(const AEnemyBase& _Other) = delete;
	AEnemyBase(AEnemyBase&& _Other) noexcept = delete;
	AEnemyBase& operator=(const AEnemyBase& _Other) = delete;
	AEnemyBase& operator=(AEnemyBase&& _Other) noexcept = delete;

	inline USpriteRenderer* GetRenderer() const
	{
		return Renderer;
	}

	void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

protected:
	void DirChange();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;

// FSM
private:
	UStateManager State;
	void StateInit();

protected:
	virtual void IdleStart() {};
	virtual void Idle(float _DeltaTime) {};

	virtual void WalkStart() {};
	virtual void Walk(float _DeltaTime);

	virtual void FallStart() {};
	virtual void Fall(float _DeltaTime) {};

};

