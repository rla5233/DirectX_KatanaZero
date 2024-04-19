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

//FSM
protected:
	void IdleStart() override;

	void HitFallStart() override;

	void DeadStart() override;

};

