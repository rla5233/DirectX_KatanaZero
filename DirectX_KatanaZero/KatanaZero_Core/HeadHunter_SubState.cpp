#include "PreCompile.h"
#include "HeadHunter.h"

void AHeadHunter::SubStateInit()
{
	// SubState Create
	SubState.CreateState(HeadHunterSubState::wait);
	SubState.CreateState(HeadHunterSubState::play);
	SubState.CreateState(HeadHunterSubState::restart);

	// SubState Start
	SubState.SetStartFunction(HeadHunterSubState::wait,		std::bind(&AHeadHunter::WaitStart, this));
	SubState.SetStartFunction(HeadHunterSubState::play,		std::bind(&AHeadHunter::PlayStart, this));
	SubState.SetStartFunction(HeadHunterSubState::restart,	std::bind(&AHeadHunter::RestartStart, this));

	// SubState Update
	SubState.SetUpdateFunction(HeadHunterSubState::wait,	std::bind(&AHeadHunter::Wait, this, std::placeholders::_1));
	SubState.SetUpdateFunction(HeadHunterSubState::play,	std::bind(&AHeadHunter::Play, this, std::placeholders::_1));
	SubState.SetUpdateFunction(HeadHunterSubState::restart,	std::bind(&AHeadHunter::Restart, this, std::placeholders::_1));

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
	Recording(_DeltaTime);
}

void AHeadHunter::RestartStart()
{
	SetRewindStart();
	State.ChangeState(HeadHunterState::none);
}

void AHeadHunter::Restart(float _DeltaTime)
{
	Replaying(_DeltaTime);
}

