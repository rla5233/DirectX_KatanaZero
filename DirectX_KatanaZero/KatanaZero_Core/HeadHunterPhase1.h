#pragma once
#include "HeadHunterBase.h"

// Ό³Έν : Phase1 HeadHunter
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

	int RollCount = 0;

	float PatternDelayTimeCount = 0.0f;
	int Pattern1Count = 0;

// FSM
private:
	void IdleStart() override;
	void Idle(float _DeltaTime) override;

	void RecoverStart() override;

	void ExitDoorStart();
	void ExitDoor(float _DletaTime);

	void RollStart();
	void Roll(float _DeltaTime);

	void PatternRifle1Start();
	void PatternRifle1(float _DeltaTime);

	void PatternAirRifle1Start();
	void PatternAirRifle1(float _DeltaTime);

// Sub FSM
private:
	void PlayStart() override;
	void Play(float _DeltaTime) override;

// Effect
private:
	void CreateRollCroudEffect(float _DeltaTime);
	void CroudEffectUpdate(float _DeltaTime);
	
	void SetRifle1LaserEffect();

	void SetAirRifle1LaserEffect();
	void AirRifle1LaserEffectUpdate(float _DeltaTime);

// Pattern
private:
	void PatternCheck();

	// Pattern_Rifle1
	void Rifle1LaserUpdate(float _DeltaTime);
	void Rifle1LaserUpdate1(float _DeltaTime);
	void Rifle1LaserUpdate2(float _DeltaTime);
	void Rifle1LaserUpdate3(float _DeltaTime);

	// Pattern_AirRifle1
	void AirRifle1Update(float _DeltaTime);
	void AirRifle1Update1(float _DeltaTime);
	void AirRifle1Update2(float _DeltaTime);
	void AirRifle1Update3(float _DeltaTime);

};

