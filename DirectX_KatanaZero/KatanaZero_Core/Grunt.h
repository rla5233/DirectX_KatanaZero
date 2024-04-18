#pragma once
#include "EnemyBase.h"

// ¼³¸í : Àû Grunt
class AGrunt : public AEnemyBase
{
	GENERATED_BODY(AEnemyBase)
public:
	// constrcuter destructer
	AGrunt();
	~AGrunt();

	// delete Function
	AGrunt(const AGrunt& _Other) = delete;
	AGrunt(AGrunt&& _Other) noexcept = delete;
	AGrunt& operator=(const AGrunt& _Other) = delete;
	AGrunt& operator=(AGrunt&& _Other) noexcept = delete;

	inline void SetPatrolTime(float _WalkTime, float _StopTime)
	{
		PatrolWalkTime = _WalkTime;
		PatrolStopTime = _StopTime;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float PatrolWalkTime = 0.0f;
	float PatrolStopTime = 0.0f;

private:
	void CreateAnimation();
// FSM
protected:
	void IdleStart() override;

	void HitFallStart() override;

	void DeadStart() override;

	void PatrolWalkStart() override;
	void PatrolTurnStart() override;
	void PatrolStopStart() override;
	
	void RunStart() override;
	void Run(float _DeltaTime) override;

	void TurnStart() override;
	void Turn(float _DeltaTime) override;

 };

