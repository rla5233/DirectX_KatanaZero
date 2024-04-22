#pragma once
#include "RecMapCompoBase.h"

// 설명 : 천장 레이저
class ACeilLaser : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constrcuter destructer
	ACeilLaser();
	~ACeilLaser();

	// delete Function
	ACeilLaser(const ACeilLaser& _Other) = delete;
	ACeilLaser(ACeilLaser&& _Other) noexcept = delete;
	ACeilLaser& operator=(const ACeilLaser& _Other) = delete;
	ACeilLaser& operator=(ACeilLaser&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* HitCol = nullptr;

protected:
	void StateInit() override;

};

