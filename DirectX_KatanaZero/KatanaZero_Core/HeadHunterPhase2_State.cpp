#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"

void AHeadHunterPhase2::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadHunterState::pattern_gunshoot1);
	State.CreateState(HeadHunterState::sword_dash);

	// State Start
	State.SetStartFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1Start, this));
	State.SetStartFunction(HeadHunterState::sword_dash,				std::bind(&AHeadHunterPhase2::PatternSwordDashStart, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::sword_dash,			std::bind(&AHeadHunterPhase2::PatternSwordDash, this, std::placeholders::_1));

	// State End
	State.SetEndFunction(HeadHunterState::pattern_gunshoot1, [=] 
		{ 
			IsGunShoot = false;
			Body->SetPosition(FVector::Zero); 
		}
	);
	 
	State.SetEndFunction(HeadHunterState::sword_dash, [=]
		{
			DashLaser->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
			DashLaser->SetActive(false);
		}
	);
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
		//State.ChangeState(HeadHunterState::pattern_gunshoot1);
		State.ChangeState(HeadHunterState::sword_dash);
		return;
	}
}

void AHeadHunterPhase2::PatternGunShoot1Start()
{
	Body->ChangeAnimation(Anim::headhunter_takeout_gun);
	AdjustBodyPosByDir({ 13.0f, 0.0f, 0.0f });
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

void AHeadHunterPhase2::PatternSwordDashStart()
{
	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	float CurPosX = GetActorLocation().X;

	float WallPosX = 0.0f;
	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		WallPosX = PlayLevel->GetRefPosX(HH_Phase2_RefPos::leftwall);
		DashLaser->SetScale({ CurPosX - WallPosX, 2.0f, 0.0f });
		DashLaser->SetPosition({ -70.0f - 0.5f * (CurPosX - WallPosX), 35.0f, 0.0f});
		Body->SetPosition({ -19.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		WallPosX = PlayLevel->GetRefPosX(HH_Phase2_RefPos::rightwall);
		DashLaser->SetScale({ WallPosX - CurPosX, 2.0f, 0.0f });
		DashLaser->SetPosition({ 70.0f + 0.5f * (WallPosX - CurPosX), 35.0f, 0.0f });
		Body->SetPosition({ 19.0f, 0.0f, 0.0f });
		break;
	}

	DashLaserAlpha = 0.0f;
	Body->ChangeAnimation(Anim::headhunter_predash);
	DashLaser->SetMulColor({ 1.0f, 1.0f, 1.0f, DashLaserAlpha });
	DashLaser->SetActive(true);
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternSwordDash(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		SwordDashUpdate(_DeltaTime);
		break;
	case 1:
		SwordDashUpdate1(_DeltaTime);
		break;
	case 2:
		SwordDashUpdate2(_DeltaTime);
		break;
	default:
		break;
	}

}


