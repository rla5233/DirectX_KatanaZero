#include "PreCompile.h"
#include "HeadHunterBase.h"

void AHeadHunterBase::SubStateInit()
{
	// SubState Create
	SubState.CreateState(HeadHunterSubState::wait);
	SubState.CreateState(HeadHunterSubState::play);
	SubState.CreateState(HeadHunterSubState::restart);

	// SubState Start
	SubState.SetStartFunction(HeadHunterSubState::wait,		std::bind(&AHeadHunterBase::WaitStart, this));
	SubState.SetStartFunction(HeadHunterSubState::play,		std::bind(&AHeadHunterBase::PlayStart, this));
	SubState.SetStartFunction(HeadHunterSubState::restart,	std::bind(&AHeadHunterBase::RestartStart, this));

	// SubState Update
	SubState.SetUpdateFunction(HeadHunterSubState::wait,	std::bind(&AHeadHunterBase::Wait, this, std::placeholders::_1));
	SubState.SetUpdateFunction(HeadHunterSubState::play,	std::bind(&AHeadHunterBase::Play, this, std::placeholders::_1));
	SubState.SetUpdateFunction(HeadHunterSubState::restart,	std::bind(&AHeadHunterBase::Restart, this, std::placeholders::_1));

}

void AHeadHunterBase::WaitStart()
{
}

void AHeadHunterBase::Wait(float _DeltaTime)
{
}

void AHeadHunterBase::PlayStart()
{
}

void AHeadHunterBase::Play(float _DeltaTime)
{
	Recording(_DeltaTime);
}

void AHeadHunterBase::RestartStart()
{
	SetRewindStart();
	State.ChangeState(HeadHunterState::none);
}

void AHeadHunterBase::Restart(float _DeltaTime)
{
	Replaying(_DeltaTime);
}

