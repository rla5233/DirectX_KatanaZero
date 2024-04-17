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

private:
	void CreateAnimation();
// FSM
protected:
	void IdleStart() override;
	void Idle(float _DeltaTime) override;

	void WalkStart() override;
	void Walk(float _DeltaTime) override;

 };

