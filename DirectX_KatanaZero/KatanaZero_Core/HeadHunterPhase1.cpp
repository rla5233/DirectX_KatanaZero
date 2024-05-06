#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"

AHeadHunterPhase1::AHeadHunterPhase1()
{
}

AHeadHunterPhase1::~AHeadHunterPhase1()
{
}

void AHeadHunterPhase1::BeginPlay()
{
	Super::BeginPlay();
}

void AHeadHunterPhase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunterPhase1::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(HeadHunterState::roll);
	State.CreateState(HeadHunterState::exitdoor);

	// State Start
	State.SetStartFunction(HeadHunterState::roll,		std::bind(&AHeadHunterPhase1::RollStart, this));
	State.SetStartFunction(HeadHunterState::exitdoor,	std::bind(&AHeadHunterPhase1::ExitDoorStart, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::roll,		std::bind(&AHeadHunterPhase1::Roll, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::exitdoor,	std::bind(&AHeadHunterPhase1::ExitDoor, this, std::placeholders::_1));

}

void AHeadHunterPhase1::Idle(float _DeltaTime)
{
	Super::Idle(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE))
	{
		State.ChangeState(HeadHunterState::roll);
		return;
	}
}

void AHeadHunterPhase1::RecoverStart()
{
	Super::RecoverStart();

	DelayCallBack(3.0f, [=]
		{
			State.ChangeState(HeadHunterState::exitdoor);
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
	
	DelayCallBack(0.6f, [=]
		{
			State.ChangeState(HeadHunterState::pattern_rifle1);
		}
	);
}

void AHeadHunterPhase1::ExitDoor(float _DletaTime)
{
}

void AHeadHunterPhase1::RollStart()
{
	Body->ChangeAnimation(Anim::headhunter_roll);

	SetVelocityByDir({ 600.0f, 0.0f, 0.0f });
}

void AHeadHunterPhase1::Roll(float _DeltaTime)
{
	FVector Vel = { -400.0f * _DeltaTime, 0.0f, 0.0f };
	AddVelocityByDir(Vel);

	// 위치 업데이트
	PosUpdate(_DeltaTime);


}
