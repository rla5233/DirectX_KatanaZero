#pragma once
#include "EnemyBase.h"

// ¼³¸í : Àû GangSter
class AGangSter : public AEnemyBase
{
	GENERATED_BODY(AEnemyBase)
public:
	// constrcuter destructer
	AGangSter();
	~AGangSter();

	// delete Function
	AGangSter(const AGangSter& _Other) = delete;
	AGangSter(AGangSter&& _Other) noexcept = delete;
	AGangSter& operator=(const AGangSter& _Other) = delete;
	AGangSter& operator=(AGangSter&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionInit() override;

private:
	void CreateAnimation();

private:
	USpriteRenderer* Spark = nullptr;

	float AttackRange = 450.0f;

//FSM
protected:
	void IdleStart() override;

	void HitFallStart() override;

	void DeadStart() override;

	void ChaseRunStart() override;
	void ChaseRunEnd() override;
	void ChaseStopStart() override;
	void ChaseTurnStart() override;

	void ChaseStairUpStart() override;
	void ChaseStairDownStart() override;
	void ChaseStairTurnStart() override;

	void ChaseAttackStart() override;
	void ChaseAttack(float _DeltaTime) override;

	bool AttackRangeCheck() override;

protected:
	void ChaseMarkUpdate() override;

// Effect
private:
	void SetAttackEffect();

};

