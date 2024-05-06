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

// FSM
private:
	void RecoverStart() override;

	void ExitDoorStart();
	void ExitDoor(float _DletaTime);

};

