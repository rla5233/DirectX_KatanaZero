#include "PreCompile.h"
#include "TitleGameMode.h"

#include "MainCamera.h"
#include "TitleScreen.h"
#include "TitleMenu.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()	
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	StateInit();
}

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	State.ChangeState(TitleLevelState::title);
}

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Screen->Destroy();
	Menu->Destroy();

	Screen = nullptr;
	Menu = nullptr;
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ATitleGameMode::StateInit()
{
	// State Create
	State.CreateState(TitleLevelState::title);
	State.CreateState(TitleLevelState::wait);
	State.CreateState(TitleLevelState::exit);

	// State Start
	State.SetStartFunction(TitleLevelState::title, [=]
		{
			MainCamera = GetWorld()->SpawnActor<AMainCamera>("MainCamera");
			
			FVector CameraStartPos = { 0.0f, 0.0f, -100.0f };
			FVector CameraTargetPos = { 0.0f, -360.0f, -100.0f };
			MainCamera->SetLerpMovePos(CameraStartPos, CameraTargetPos);

			Screen = GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");
		}
	);

	State.SetStartFunction(TitleLevelState::wait, [=] {});
	State.SetStartFunction(TitleLevelState::exit, [=] {});

	// State Update
	State.SetUpdateFunction(TitleLevelState::title, [=] (float _DeltaTime)
		{
			MainCamera->LerpMoveUpdate(_DeltaTime, EnterTitleTimeWeight);
			EnterTitleTimeWeight -= 2.0f * _DeltaTime;

			if (false == MainCamera->IsLerpMove())
			{
				Menu = GetWorld()->SpawnActor<ATitleMenu>("TitleMenu");
				State.ChangeState(TitleLevelState::wait);
				return;
			}
		}
	);

	State.SetUpdateFunction(TitleLevelState::wait, [=](float _DeltaTime) {});
	State.SetUpdateFunction(TitleLevelState::exit, [=](float _DeltaTime) {});
}

void ATitleGameMode::InputCheck(int _Input)
{
	switch (_Input)
	{
	case 0:
		Screen->StateChange(TitleScreenState::newgame);
		break;
	case 4:
		Screen->StateChange(TitleScreenState::exit);
		break;
	default:
		break;
	}
}

void ATitleGameMode::MenuInputOff()
{
	Menu->InputOff();
}