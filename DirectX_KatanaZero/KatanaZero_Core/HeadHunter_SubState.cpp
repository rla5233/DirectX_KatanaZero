#include "PreCompile.h"
#include "HeadHunter.h"

void AHeadHunter::SubStateInit()
{
	// SubState Create
	SubState.CreateState(HeadHunterSubState::wait);
	SubState.CreateState(HeadHunterSubState::play);

	// SubState Start
	SubState.SetStartFunction(HeadHunterSubState::wait,		std::bind(&AHeadHunter::WaitStart, this));
	SubState.SetStartFunction(HeadHunterSubState::play,		std::bind(&AHeadHunter::PlayStart, this));

	// SubState Update
	SubState.SetUpdateFunction(HeadHunterSubState::wait,	std::bind(&AHeadHunter::Wait, this, std::placeholders::_1));
	SubState.SetUpdateFunction(HeadHunterSubState::play,	std::bind(&AHeadHunter::Play, this, std::placeholders::_1));

}

void AHeadHunter::WaitStart()
{
}

void AHeadHunter::Wait(float _DeltaTime)
{
}

void AHeadHunter::PlayStart()
{
	State.ChangeState(HeadHunterState::pattern_rifle1);
}

void AHeadHunter::Play(float _DeltaTime)
{

}

