#pragma once
#include "HeadHunterBase.h"

// Ό³Έν :
class AHeadHunterPhase1 : public AHeadHunterBase
{
	GENERATED_BODY(AHeadHunterBase)
public:
	// constructor destructor
	AHeadHunterPhase1();
	~AHeadHunterPhase1();
	
	// delete Function
	AHeadHunterPhase1(const AHeadHunterPhase1& _Other) = delete;
	AHeadHunterPhase1(AHeadHunterPhase1&& _Other) noexcept = delete;
	AHeadHunterPhase1& operator=(const AHeadHunterPhase1& _Other) = delete;
	AHeadHunterPhase1& operator=(AHeadHunterPhase1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void StateInit() override;

private:
	std::vector<UCloudEffect> Cloud;
	float CroudTimeCount = 0.0f;
	const int CloudSize = 15;
	int CloudIdx = 0;

// FSM
private:
	void Idle(float _DeltaTime) override;

	void RecoverStart() override;

	void ExitDoorStart();
	void ExitDoor(float _DletaTime);

	void RollStart();
	void Roll(float _DeltaTime);

// Sub FSM
private:
	void Play(float _DeltaTime) override;


// Effect
private:
	void CreateRollCroudEffect(float _DeltaTime);
	void CroudEffectUpdate(float _DeltaTime);


};

