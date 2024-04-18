#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"
#include "RecordingObject.h"

// Ό³Έν :
class AEnemyBase : 
	public AActor, 
	public UPixelColObject, 
	public UPhysicsObject, 
	public URecordingObject
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

	inline void SetTimeCount(float _Time)
	{
		TimeCount = _Time;
	}

	inline void SetRendererDir(EEngineDir _Dir)
	{
		Renderer->SetDir(_Dir);
	}

	void SetVelocityByDir(const FVector& _Vel);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void DefaultUpdate(float _DeltaTime);

	void RendererDirChange();

private:
	USpriteRenderer* Renderer = nullptr;
	float TimeCount = 0.0f;

// FSM
private:
	UStateManager State;
	void StateInit();

protected:
	virtual void IdleStart() {};
	virtual void Idle(float _DeltaTime) {};

	virtual void PatrolWalkStart() {};
	virtual void PatrolWalk(float _DeltaTime);

	virtual void PatrolTurnStart();
	virtual void PatrolTurn(float _DeltaTime);

	virtual void PatrolStopStart();
	virtual void PatrolStop(float _DeltaTime);

	virtual void RunStart() {};
	virtual void Run(float _DeltaTime);

	virtual void TurnStart();
	virtual void Turn(float _DeltaTime);

	virtual void FallStart() {};
	virtual void Fall(float _DeltaTime) {};

};

