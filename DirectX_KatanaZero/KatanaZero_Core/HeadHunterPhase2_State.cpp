#include "PreCompile.h"
#include "HeadHunterPhase2.h"


void AHeadHunterPhase2::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadHunterState::pattern_gunshoot1);

	// State Start
	State.SetStartFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1Start, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1, this, std::placeholders::_1));

}

void AHeadHunterPhase2::IdleStart()
{
	Super::IdleStart();

	PatternDelayTimeCount = 0.015f;
}

void AHeadHunterPhase2::Idle(float _DeltaTime)
{
	Super::Idle(_DeltaTime);

	if (HeadHunterSubState::play != SubState.GetCurStateName())
	{
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		State.ChangeState(HeadHunterState::pattern_gunshoot1);
		return;
	}
}

void AHeadHunterPhase2::PatternGunShoot1Start()
{
	Body->ChangeAnimation(Anim::headhunter_takeout_gun);

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetPosition({ -13.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ 13.0f, 0.0f, 0.0f });
		break;
	}

	GunShootCount = 3;
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternGunShoot1(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		GunShoot1Update(_DeltaTime);
		break;
	case 1:
		GunShoot1Update1(_DeltaTime);
		break;
	default:
		break;
	}

}


