#pragma once
#include "EnemyBase.h"

// ���� : �� Grunt
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionInit() override;

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

	void TurnStart() override;

 };

