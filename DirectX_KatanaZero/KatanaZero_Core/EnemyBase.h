#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject_Base.h"
#include "PhysicsObject.h"

// Ό³Έν :
class AEnemyBase : public APixelColObject_Base, public UPhysicsObject
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;

// FSM
private:
	UStateManager State;
	void StateInit();

	virtual void IdleStart() {};
	virtual void Idle(float _DeltaTime) {};

};

