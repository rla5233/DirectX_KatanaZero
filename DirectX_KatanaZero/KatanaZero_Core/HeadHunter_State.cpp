#include "PreCompile.h"
#include "HeadHunter.h"

void AHeadHunter::StateInit()
{
	// State Create
	State.CreateState(HeadHunterState::idle);

	// State Start
	State.SetStartFunction(HeadHunterState::idle, std::bind(&AHeadHunter::IdleStart, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::idle, std::bind(&AHeadHunter::Idle, this, std::placeholders::_1));

}

void AHeadHunter::IdleStart()
{
	Body->ChangeAnimation(Anim::headhunter_idle);
}

void AHeadHunter::Idle(float _DeltaTime)
{
}
