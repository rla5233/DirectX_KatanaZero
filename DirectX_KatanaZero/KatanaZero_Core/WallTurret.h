#pragma once
#include "RecMapCompoBase.h"

// Ό³Έν : HeadHunter WallTurret
class AWallTurret : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constructor destructor
	AWallTurret();
	~AWallTurret();
	
	// delete Function
	AWallTurret(const AWallTurret& _Other) = delete;
	AWallTurret(AWallTurret&& _Other) noexcept = delete;
	AWallTurret& operator=(const AWallTurret& _Other) = delete;
	AWallTurret& operator=(AWallTurret&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;

private:
	void WallOpenAnimAdjust();

private:
	int Order = 0;

private:
	std::vector<USpriteRenderer*> AllHolder;
	const int HolderNum = 2;

	std::vector<USpriteRenderer*> AllHead;
	std::vector<USpriteRenderer*> Spark;
	std::vector<UCollision*> HeadCol;
	std::vector<float> MinHeadRangeX = { 430.0f, 350.0f };
	std::vector<float> ShootDelayTimeCount = { 0.5f, 0.5f };
	float HeadDeg_Min = 320.0f;
	const int HeadNum = 2;

	const float ShootDelayTime = 2.0f;


};

