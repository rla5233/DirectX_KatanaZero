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

class AUpMark;
class AStair;

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

	void SetBodyDir(EEngineDir _Dir);
	void SetVelocityByDir(const FVector& _Vel);

	void HitByPlayer(FVector _AttDir);
	void HitByDoor(EEngineDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// Init
	void RendererInit();
	void EffectInit();
	virtual void CollisionInit();

	// Collision
	UCollision* BodyCol = nullptr;
	UCollision* DeadCol = nullptr;

private:
	// Renderer
	USpriteRenderer* Body = nullptr;

	// Blood Effect
	std::vector<BloodEffect> Blood;
	static const int BloodSize;
	float BloodTimeCount = 0.0f;
	int BloodIdx = 0;

	// Hit State
	FVector HitDir = FVector::Zero;

	// Patrol State
	float PatrolWalkTime = 0.0f;
	float PatrolStopTime = 0.0f;

	// Chase
	int FloorNum = -1;
	std::shared_ptr<AStair> TargetStair = nullptr;
	std::shared_ptr<AUpMark> ChaseMark = nullptr;

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
	virtual void IdleStart();
	void Idle(float _DeltaTime);
	
	virtual void HitFallStart();
	void HitFall(float _DeltaTime);

	virtual void DeadStart();
	void Dead(float _DeltaTime);

	virtual void PatrolWalkStart();
	void PatrolWalk(float _DeltaTime);

	virtual void PatrolTurnStart();
	void PatrolTurn(float _DeltaTime);

	virtual void PatrolStopStart();
	void PatrolStop(float _DeltaTime);

	virtual void ChaseRunStart();
	void ChaseRun(float _DeltaTime);

	virtual void ChaseTurnStart();
	void ChaseTurn(float _DeltaTime);

	virtual void ChaseStairUpStart();
	void ChaseStairUp(float _DeltaTime);

	virtual void ChaseStairDownStart();
	void ChaseStairDown(float _DeltaTime);

	virtual void ChaseStairTurnStart();
	void ChaseStairTurn(float _DeltaTime);

	virtual void ChaseAttackStart();
	virtual void ChaseAttack(float _DeltaTime);

protected:
	void DirChange();
	bool PlayerChaseCheck();

	bool ChaseTurnCheck();
	bool ChaseSameFloorCheck();
	std::shared_ptr<AStair> FindStair();

	virtual bool AttackRangeCheck();

// Effect
private:
	void BloodVecIdxUpdate();
	void CreateBloodEffect(float _DeltaTime);
	void BloodEffectUpdate(float _DeltaTime);

private:
	void FloorNumUpdate();
};

