#pragma once
#include "RecMapCompoBase.h"

// ���� : HeadHunter WallTurret
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
	std::vector<float> MinHeadRangeX;
	const int HeadNum = 2;

	float HeadDeg_Min = 320.0f;

};

