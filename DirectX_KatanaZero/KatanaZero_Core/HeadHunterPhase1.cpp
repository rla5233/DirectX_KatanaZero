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
	State.CreateState(HeadHunterState::exitdoor);

	// State Start
	State.SetStartFunction(HeadHunterState::exitdoor, std::bind(&AHeadHunterPhase1::ExitDoorStart, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::exitdoor, std::bind(&AHeadHunterPhase1::ExitDoor, this, std::placeholders::_1));

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