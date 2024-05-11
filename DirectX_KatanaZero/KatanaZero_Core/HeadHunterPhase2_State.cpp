#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"

void AHeadHunterPhase2::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadHunterState::pattern_rifle1);
	State.CreateState(HeadHunterState::pattern_gunshoot1);
	State.CreateState(HeadHunterState::pattern_sword_dash);
	State.CreateState(HeadHunterState::pattern_airrifle1);
	State.CreateState(HeadHunterState::pattern_airrifle2);

	// State Start
	State.SetStartFunction(HeadHunterState::pattern_rifle1,			std::bind(&AHeadHunterPhase2::PatternRifle1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_sword_dash,		std::bind(&AHeadHunterPhase2::PatternSwordDashStart, this));
	State.SetStartFunction(HeadHunterState::pattern_airrifle1,		std::bind(&AHeadHunterPhase2::PatternAirRifle1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_airrifle2,		std::bind(&AHeadHunterPhase2::PatternAirRifle2Start, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::pattern_rifle1,		std::bind(&AHeadHunterPhase2::PatternRifle1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_sword_dash,	std::bind(&AHeadHunterPhase2::PatternSwordDash, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_airrifle1,		std::bind(&AHeadHunterPhase2::PatternAirRifle1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_airrifle2,		std::bind(&AHeadHunterPhase2::PatternAirRifle2, this, std::placeholders::_1));

	// State End
	State.SetEndFunction(HeadHunterState::pattern_rifle1,		[=] { Body->SetPosition(FVector::Zero); });
	State.SetEndFunction(HeadHunterState::pattern_gunshoot1,	[=] 
		{ 
			IsGunShoot = false;
			Body->SetPosition(FVector::Zero); 
		}
	);
	 
	State.SetEndFunction(HeadHunterState::pattern_sword_dash, [=]
		{
			Body->SetPosition(FVector::Zero);
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
		//State.ChangeState(HeadHunterState::pattern_sword_dash);
		//State.ChangeState(HeadHunterState::pattern_rifle1);
		//State.ChangeState(HeadHunterState::pattern_airrifle1);
		State.ChangeState(HeadHunterState::pattern_airrifle2);
		return;
	}
}

void AHeadHunterPhase2::HitFlyStart()
{
	Super::HitFlyStart();

	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	switch (HitCount)
	{
	case 1:
		DelayCallBack(0.5f, [=] { PlayLevel->SetWallTurret(); });
		DelayCallBack(3.5f, [=] { State.ChangeState(HeadHunterState::pattern_airrifle2); });
		break;
	}
}

void AHeadHunterPhase2::PatternRifle1Start()
{
	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	FVector CurPos = GetActorLocation();

	if (PlayerPos.X < CurPos.X)
	{
		Body->SetDir(EEngineDir::Left);
		Body->AddPosition({ -6.0f, 0.0f, 0.0f });
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
		Body->AddPosition({ 6.0f, 0.0f, 0.0f });
	}

	Body->ChangeAnimation(Anim::headhunter_takeup_rifle);
	AllRifleLaserAlpha[RifleLaserIdx] = 1.0f;
	RollCount = 0;
	Rifle1Count = 3;
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternRifle1(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		Rifle1LaserUpdate(_DeltaTime);
		break;
	case 1:
		Rifle1LaserUpdate1(_DeltaTime);
		break;
	case 2:
		Rifle1LaserUpdate2(_DeltaTime);
		break;
	case 3:
		Rifle1LaserUpdate3(_DeltaTime);
		break;
	default:
		break;
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
		WallPosX = PlayLevel->GetRefPos(HH_Phase2_RefPos::leftwall);
		DashLaser->SetScale({ CurPosX - WallPosX, 2.0f, 0.0f });
		DashLaser->SetPosition({ -70.0f - 0.5f * (CurPosX - WallPosX), 35.0f, 0.0f});
		Body->SetPosition({ -19.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		WallPosX = PlayLevel->GetRefPos(HH_Phase2_RefPos::rightwall);
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
	default:
		break;
	}
}

void AHeadHunterPhase2::PatternAirRifle1Start()
{
	Body->ChangeAnimation(Anim::headhunter_prejump);
	AdjustBodyPosByDir({ 11.0f, 0.0f, 0.0f });
	BodyCol->SetActive(false);
	RollCount = 0;
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternAirRifle1(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		AirRifle1Update(_DeltaTime);
		break;
	case 1:
		AirRifle1Update1(_DeltaTime);
		break;
	case 2:
		AirRifle1Update2(_DeltaTime);
		break;
	case 3:
		AirRifle1Update3(_DeltaTime);
		break;
	default:
		break;
	}
}

void AHeadHunterPhase2::PatternAirRifle2Start()
{
	Body->ChangeAnimation(Anim::headhunter_tel_in_sweep);
	Body->SetDir(EEngineDir::Right);
	SetActorLocation({ 620.0f, 450.0f, 0.0f });
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternAirRifle2(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		AirRifle2Update(_DeltaTime);
		break;
	case 1:
		AirRifle2Update1(_DeltaTime);
		break;
	case 2:
		AirRifle2Update2(_DeltaTime);
		break;
	default:
		break;
	}
}


