#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"
#include "HeadHunterLevel_Phase1.h"

void AHeadHunterPhase1::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadHunterState::roll);
	State.CreateState(HeadHunterState::exitdoor);
	State.CreateState(HeadHunterState::pattern_rifle1);
	State.CreateState(HeadHunterState::pattern_airrifle1);

	// State Start
	State.SetStartFunction(HeadHunterState::roll,				std::bind(&AHeadHunterPhase1::RollStart, this));
	State.SetStartFunction(HeadHunterState::exitdoor,			std::bind(&AHeadHunterPhase1::ExitDoorStart, this));
	State.SetStartFunction(HeadHunterState::pattern_rifle1,		std::bind(&AHeadHunterPhase1::PatternRifle1Start, this));
	State.SetStartFunction(HeadHunterState::pattern_airrifle1,	std::bind(&AHeadHunterPhase1::PatternAirRifle1Start, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::roll,				std::bind(&AHeadHunterPhase1::Roll, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::exitdoor,			std::bind(&AHeadHunterPhase1::ExitDoor, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_rifle1,	std::bind(&AHeadHunterPhase1::PatternRifle1, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_airrifle1,	std::bind(&AHeadHunterPhase1::PatternAirRifle1, this, std::placeholders::_1));
	
	// State End
	State.SetEndFunction(HeadHunterState::roll,					[=] { BodyCol->SetActive(true); });
	State.SetEndFunction(HeadHunterState::pattern_rifle1,		[=] { Body->SetPosition(FVector::Zero); });
	State.SetEndFunction(HeadHunterState::pattern_airrifle1,	[=] { BodyCol->SetActive(true); });

}

void AHeadHunterPhase1::IdleStart()
{
	Super::IdleStart();

	PatternDelayTimeCount = 0.015f;
}

void AHeadHunterPhase1::Idle(float _DeltaTime)
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

void AHeadHunterPhase1::RecoverStart()
{
	Super::RecoverStart();

	LaserCol->SetActive(false);
	LaserEffect->SetActive(false);

	DelayCallBack(1.5f, [=]
		{
			if (0 < Hp)
			{
				DelayCallBack(1.5f, [=]
					{
						State.ChangeState(HeadHunterState::exitdoor);
						return;
					}
				);
			}
			else
			{
				IsDeadValue = true;
			}
		}
	);
}

void AHeadHunterPhase1::ExitDoorStart()
{
	AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
	FVector NextPos = PlayLevel->FindExitDoor();
	SetActorLocation(NextPos);

	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	if (PlayerPos.X < NextPos.X)
	{
		Body->SetDir(EEngineDir::Left);
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
	}

	Body->ChangeAnimation(Anim::headhunter_exit_door);
	RollCount = 0;
}

void AHeadHunterPhase1::ExitDoor(float _DletaTime)
{
}

void AHeadHunterPhase1::RollStart()
{
	AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
	float MidPosX = PlayLevel->GetRefPosX(HH_Phase1_RefPos::mid);
	float CurPosX = GetActorLocation().X;

	// 속도 설정
	if (MidPosX < CurPosX)
	{
		Body->SetDir(EEngineDir::Left);
		Velocity = { -650.0f, 0.0f, 0.0f };
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
		Velocity = { 650.0f, 0.0f, 0.0f };
	}

	Body->ChangeAnimation(Anim::headhunter_roll);
	CroudTimeCount = Const::effect_roll_cloud_delay;

	SetAfterImagePlusColor({ 1.0f, 0.0f, 1.0f });
	SetAfterImageAlphaWeight(0.6f);
	SetAfterImageTimeWeight(6.0f);

	BodyCol->SetActive(false);

	++RollCount;
	PatternOrder = 0;
}

void AHeadHunterPhase1::Roll(float _DeltaTime)
{
	// 속도 업데이트
	FVector Vel = { -400.0f * _DeltaTime, 0.0f, 0.0f };
	AddVelocityByDir(Vel);

	if (true == IsColHeadToWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// Effect
	CreateRollCroudEffect(_DeltaTime);
	if (1 <= Body->GetCurAnimationFrame())
	{
		CreateAfterImage(_DeltaTime);
	}
}

void AHeadHunterPhase1::PatternRifle1Start()
{
	AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
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
	RollCount = 0;
	Pattern1Count = 3;
	PatternOrder = 0;
}

void AHeadHunterPhase1::PatternRifle1(float _DeltaTime)
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

void AHeadHunterPhase1::PatternAirRifle1Start()
{
	Body->ChangeAnimation(Anim::headhunter_prejump);

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetPosition({ -11.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ 11.0f, 0.0f, 0.0f });
		break;
	}

	BodyCol->SetActive(false);
	RollCount = 0;
	PatternOrder = 0;
}

void AHeadHunterPhase1::PatternAirRifle1(float _DeltaTime)
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