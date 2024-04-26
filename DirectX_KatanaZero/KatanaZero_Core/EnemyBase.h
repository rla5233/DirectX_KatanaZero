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
	virtual void CollisionInit();

	UCollision* BodyCol = nullptr;
	UCollision* DeadCol = nullptr;

private:
	void RendererDirChange();

private:
	USpriteRenderer* Body = nullptr;
	std::vector<BloodEffect> Blood;
	static const int BloodSize;
	int BloodIdx = 0;

	FVector HitDir = FVector::Zero;
	float TimeCount = 0.0f;

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
	virtual void Idle(float _DeltaTime) { Recording(_DeltaTime); };

	virtual void PatrolWalkStart();
	virtual void PatrolWalk(float _DeltaTime);

	virtual void PatrolTurnStart();
	virtual void PatrolTurn(float _DeltaTime);

	virtual void PatrolStopStart();
	virtual void PatrolStop(float _DeltaTime);

	float PatrolWalkTime = 0.0f;
	float PatrolStopTime = 0.0f;

	virtual void RunStart() {};
	virtual void Run(float _DeltaTime);

	virtual void TurnStart();
	virtual void Turn(float _DeltaTime);

	virtual void HitFallStart();
	virtual void HitFall(float _DeltaTime);

	virtual void DeadStart() {};
	virtual void Dead(float _DeltaTime);

// Effect
private:
	void BloodVecIdxUpdate();
	void CreateBloodEffect(float _DeltaTime);
	void BloodEffectUpdate(float _DeltaTime);
	float BloodTimeCount = 0.0f;


};

