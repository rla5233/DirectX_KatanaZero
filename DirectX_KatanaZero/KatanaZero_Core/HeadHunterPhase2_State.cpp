#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
#include "DefaultPlayer.h"
#include "MainCamera.h"

void AHeadHunterPhase2::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadHunterState::pattern_rifle1);
	State.CreateState(HeadHunterState::pattern_gunshoot1);
	State.CreateState(HeadHunterState::pattern_sword_dash);
	State.CreateState(HeadHunterState::pattern_airrifle1);
	State.CreateState(HeadHunterState::pattern_airrifle2);
	State.CreateState(HeadHunterState::pattern_complex);
	State.CreateState(HeadHunterState::pattern_bombing);
	State.CreateState(HeadHunterState::dead);

	// State Start
	State.SetStartFunction(HeadHunterState::pattern_rifle1,			std::bind(&AHeadHunterPhase2::PatternRifle1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_sword_dash,		std::bind(&AHeadHunterPhase2::PatternSwordDashStart, this));
	State.SetStartFunction(HeadHunterState::pattern_airrifle1,		std::bind(&AHeadHunterPhase2::PatternAirRifle1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_airrifle2,		std::bind(&AHeadHunterPhase2::PatternAirRifle2Start, this));
	State.SetStartFunction(HeadHunterState::pattern_complex,		std::bind(&AHeadHunterPhase2::PatternComplexStart, this));
	State.SetStartFunction(HeadHunterState::pattern_bombing,		std::bind(&AHeadHunterPhase2::PatternBombingStart, this));
	State.SetStartFunction(HeadHunterState::dead,					std::bind(&AHeadHunterPhase2::DeadStart, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::pattern_rifle1,		std::bind(&AHeadHunterPhase2::PatternRifle1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_gunshoot1,		std::bind(&AHeadHunterPhase2::PatternGunShoot1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_sword_dash,	std::bind(&AHeadHunterPhase2::PatternSwordDash, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_airrifle1,		std::bind(&AHeadHunterPhase2::PatternAirRifle1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_airrifle2,		std::bind(&AHeadHunterPhase2::PatternAirRifle2, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_complex,		std::bind(&AHeadHunterPhase2::PatternComplex, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_bombing,		std::bind(&AHeadHunterPhase2::PatternBombing, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::dead,					std::bind(&AHeadHunterPhase2::Dead, this, std::placeholders::_1));

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

	PatternDelayTimeCount = 0.03f;
}

void AHeadHunterPhase2::Idle(float _DeltaTime)
{
	Super::Idle(_DeltaTime);

	if (HeadHunterSubState::play != SubState.GetCurStateName())
	{
		return;
	}

	if (0.0f < PatternDelayTimeCount)
	{
		PatternDelayTimeCount -= _DeltaTime;
		return;
	}

	PatternCheck();
}

void AHeadHunterPhase2::HitFlyStart()
{
	Super::HitFlyStart();

	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	switch (HitCount)
	{
	case 1:
		DelayCallBack(0.5f, [=] { PlayLevel->SetWallTurret(); });
		DelayCallBack(3.5f, [=] 
			{ 
				if (HeadHunterSubState::restart == SubState.GetCurStateName())
				{
					return;
				}

				State.ChangeState(HeadHunterState::pattern_airrifle2); 
			}
		);
		break;
	}

	RifleLaserEffect->SetActive(false);
	RollCount = 0;
}

void AHeadHunterPhase2::RecoverStart()
{
	Super::RecoverStart();

	switch (HitCount)
	{
	case 2:
		DelayCallBack(1.4f, [=]
			{
				if (HeadHunterSubState::restart == SubState.GetCurStateName())
				{
					return;
				}

				State.ChangeState(HeadHunterState::pattern_complex);
			}
		);
		break;
	case 3:
		DelayCallBack(1.2f, [=]
			{
				if (HeadHunterSubState::restart == SubState.GetCurStateName())
				{
					return;
				}

				State.ChangeState(HeadHunterState::pattern_bombing);
			}
		);
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
	RifleLaserAlpha = 1.0f;
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
	RollCount = 0;
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
	UEngineSound::SoundPlay(SoundRes::hh_pre_knife).SetVolume(0.75f);
	Body->ChangeAnimation(Anim::headhunter_predash);
	DashLaser->SetMulColor({ 1.0f, 1.0f, 1.0f, DashLaserAlpha });
	DashLaser->SetActive(true);
	RollCount = 0;
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
	SetActorLocation({ 620.0f, 450.0f, 0.0f });
	Body->ChangeAnimation(Anim::headhunter_tel_in_sweep);
	Body->SetDir(EEngineDir::Right);
	BodyCol->SetActive(false);
	RollCount = 0;
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
	case 3:
		AirRifle2Update3(_DeltaTime);
		break;
	default:
		break;
	}
}

void AHeadHunterPhase2::PatternComplexStart()
{
	AirLaserCount = 0;
	SetActorLocation({ AirPosX[AirLaserCount], AirPosY, 0.0f });
	Body->ChangeAnimation(Anim::headhunter_tel_in);
	Body->SetDir(EEngineDir::Right);
	BodyCol->SetActive(false);
	RollCount = 0;
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternComplex(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		ComplexUpdate(_DeltaTime);
		break;
	case 1:
		ComplexUpdate1(_DeltaTime);
		break;
	case 2:
		ComplexUpdate2(_DeltaTime);
		break;
	case 3:
		ComplexUpdate3(_DeltaTime);
		break;
	case 4:
		ComplexUpdate4(_DeltaTime);
		break;
	case 5:
		ComplexUpdate5(_DeltaTime);
		break;
	case 6:
		ComplexUpdate6(_DeltaTime);
		break;
	case 7:
		ComplexUpdate7(_DeltaTime);
		break;
	case 8:
		ComplexUpdate8(_DeltaTime);
		break;
	case 9:
		ComplexUpdate9(_DeltaTime);
		break;
	case 10:
		ComplexUpdate10(_DeltaTime);
		break;
	case 11:
		ComplexUpdate11(_DeltaTime);
		break;
	default:
		break;
	}
}

void AHeadHunterPhase2::PatternBombingStart()
{
	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	FVector CurPos = GetActorLocation();
	if (CurPos.X < PlayerPos.X)
	{
		Body->SetDir(EEngineDir::Right);
	}
	else
	{
		Body->SetDir(EEngineDir::Left);
	}

	BodyCol->SetActive(false);
	DashAttack->SetActive(true);
	Body->ChangeAnimation(Anim::headhunter_reveal_bomb);
	PatternOrder = 0;
}

void AHeadHunterPhase2::PatternBombing(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		BombingUpdate(_DeltaTime);
		break;
	case 1:
		BombingUpdate1(_DeltaTime);
		break;
	case 2:
		BombingUpdate2(_DeltaTime);
		break;
	case 3:
		BombingUpdate3(_DeltaTime);
		break;
	default:
		break;
	}
}

void AHeadHunterPhase2::DeadStart()
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetDir(EEngineDir::Right);
		AddActorLocation({ 60.0f, 0.0f, 0.0f });
		SetVelocityByDir({ 1000.0f, 200.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetDir(EEngineDir::Left);
		AddActorLocation({ -60.0f, 0.0f, 0.0f });
		SetVelocityByDir({ 1000.0f, 200.0f, 0.0f });
		break;
	}

	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	PlayLevel->GetDefaultPlayer()->InputOff();
	PlayLevel->SetIsTimeCount(false);

	USoundManager::GetInst().GetHeadHunterBGM2().SetVolume(0.0f);
	GEngine->SetOrderTimeScale(EUpdateOrder::Player, 0.1f);
	GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, 0.1f);
	Body->ChangeAnimation(Anim::headhunter_diefly);
	DashAttack->SetActive(false);
	SetRecordingActive(false);
	IsDeadValue = true;
	PatternOrder = 0;
}

void AHeadHunterPhase2::Dead(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		DeadUpdate(_DeltaTime);
		break;
	case 1:
		DeadUpdate1(_DeltaTime);
		break;
	case 2:
		DeadUpdate2(_DeltaTime);
		break;
	default:
		break;
	}
}

void AHeadHunterPhase2::DeadUpdate(float _DeltaTime)
{	
	// 속도 업데이트
	ApplyGravity(_DeltaTime);
	
	// 위치 업데이트
	PosUpdate(_DeltaTime);

	if (true == IsOnGround(Body->GetDir()))
	{
		OnGroundPosAdjust(Body->GetDir());
		Body->ChangeAnimation(Anim::headhunter_dieland);

		AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
		PlayLevel->GetKZMainCamera()->SetRetShakeTime(0.1f);
		PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);

		GEngine->SetOrderTimeScale(EUpdateOrder::Player, 0.5f);
		GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, 0.5f);

		IsCameraShake = false;
		PatternOrder = 1;
	}
}

void AHeadHunterPhase2::DeadUpdate1(float _DeltaTime)
{
	if (4 == Body->GetCurAnimationFrame() && false == IsCameraShake)
	{
		AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
		PlayLevel->GetKZMainCamera()->SetRetShakeTime(0.1f);
		PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);
		IsCameraShake = true;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
		PlayLevel->GetDefaultPlayer()->InputOn();
		GEngine->SetOrderTimeScale(EUpdateOrder::Player, 1.0f);
		GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, 1.0f);
		
		SetVelocityByDir({ 15.0f, 0.0f, 0.0f });
		Body->ChangeAnimation(Anim::headhunter_dead);
		BodyCol->SetActive(true);
		PatternOrder = 2;
	}
}

void AHeadHunterPhase2::DeadUpdate2(float _DeltaTime)
{
	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// Col Check
	FVector CurPos = GetActorLocation();
	if (220.0f > CurPos.X || 1125.0f < CurPos.X)
	{
		Velocity = FVector::Zero;
	}

	BodyCol->CollisionEnter(EColOrder::PlayerAttack, [=](std::shared_ptr<UCollision> _Other)
		{
			AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			FVector HitDir = Player->GetAttackDir();
			FVector CurPos = GetActorLocation();
			EEngineDir Dir = EEngineDir::MAX;

			if (0.0f < HitDir.X)
			{
				CurPos += { 50.0f, 50.0f, 0.0f };
				Dir = EEngineDir::Right;
			}
			else
			{
				CurPos += { -50.0f, 50.0f, 0.0f };
				Dir = EEngineDir::Left;
			}

			PlayLevel->SetHeadHunterHead(CurPos, Dir);
			PlayLevel->StateChange(PlayLevelState::clear);

			USoundManager::SoundPlay_EnemyDeadSword();
			GEngine->SetGlobalTimeScale(0.01f);
			DelayCallBack(0.005f, [=] { GEngine->SetGlobalTimeScale(1.0f); });
			Body->ChangeAnimation(Anim::headhunter_dead_nohead);
			PatternOrder = -1;
		}
	);
}