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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionInit() override;
	void EffectInit();

private:
	void CreateAnimation();

private:
	UCollision* AttackCol = nullptr;
	USpriteRenderer* AttackEffect = nullptr;
	float AttackLen = 100.0f;

// FSM
protected:
	void IdleStart() override;

	void HitFallStart() override;

	void DeadStart() override;

	void PatrolWalkStart() override;
	void PatrolTurnStart() override;
	void PatrolStopStart() override;

	void ChaseRunStart() override;
	void ChaseTurnStart() override;
	void ChaseAttackStart() override;

// Effect
private:
	void SetAttackEffect(float _Deg);
	void SetAttackCollision(const FVector& _Dir, float _Deg);

 };

