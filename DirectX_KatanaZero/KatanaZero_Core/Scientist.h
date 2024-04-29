#pragma once
#include "RecMapCompoBase.h"

// Ό³Έν : Factory_005 - Scientist
class AScientist : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constrcuter destructer
	AScientist();
	~AScientist();

	// delete Function
	AScientist(const AScientist& _Other) = delete;
	AScientist(AScientist&& _Other) noexcept = delete;
	AScientist& operator=(const AScientist& _Other) = delete;
	AScientist& operator=(AScientist&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void RendererInit();
	void CollisionInit();
	void CreateAnimation();

	void StateInit() override;

private:
	UCollision* BodyCol = nullptr;

};

