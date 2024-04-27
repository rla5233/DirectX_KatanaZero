#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"
#include "RecordingObject.h"

class BloodEffect
{
public:
	USpriteRenderer* Renderer = nullptr;
	FVector Velocity = FVector::Zero;
};

// 설명 :
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

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

	void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline void SetPatrolTime(float _WalkTime, float _StopTime)
	{
		PatrolWalkTime = _WalkTime;
		PatrolStopTime = _StopTime;
	}

	inline void SetBodyDir(EEngineDir _Dir)
	{
		Body->SetDir(_Dir);
	}

	void SetVelocityByDir(const FVector& _Vel);

	void HitByPlayer(FVector _AttDir);
	void HitByDoor(EEngineDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void EffectInit();

	// Collision
	virtual void CollisionInit();
	UCollision* BodyCol = nullptr;
	UCollision* DeadCol = nullptr;

private:
	void RendererDirChange();

private:
	// Blood Effect
	USpriteRenderer* Body = nullptr;
	std::vector<BloodEffect> Blood;
	static const int BloodSize;
	float BloodTimeCount = 0.0f;
	int BloodIdx = 0;

	// Patrol State
	float PatrolWalkTime = 0.0f;
	float PatrolStopTime = 0.0f;

	// etc.
	FVector HitDir = FVector::Zero;

	// 수정 (삭제 필요)
	USpriteRenderer* RendererFT = nullptr;
	USpriteRenderer* RendererFB = nullptr;
	USpriteRenderer* RendererBT = nullptr;
	USpriteRenderer* RendererBB = nullptr;
	void DebugingRendererInit();
	void DebugingUpdate();

// FSM
private:
	UStateManager State;
	void StateInit();

protected:
	virtual void IdleStart() {};
	void Idle(float _DeltaTime);
	
	virtual void RunStart() {};
	virtual void Run(float _DeltaTime);
	
	virtual void HitFallStart();
	void HitFall(float _DeltaTime);

	virtual void DeadStart();
	void Dead(float _DeltaTime);

	virtual void PatrolWalkStart();
	void PatrolWalk(float _DeltaTime);

	virtual void PatrolTurnStart();
	void PatrolTurn(float _DeltaTime);
	void PatrolTurnEnd();

	virtual void PatrolStopStart();
	void PatrolStop(float _DeltaTime);






	virtual void ChaseStart();
	virtual void Chase(float _DeltaTime);

	virtual void TurnStart();
	virtual void Turn(float _DeltaTime);

// Effect
private:
	void BloodVecIdxUpdate();
	void CreateBloodEffect(float _DeltaTime);
	void BloodEffectUpdate(float _DeltaTime);

};

