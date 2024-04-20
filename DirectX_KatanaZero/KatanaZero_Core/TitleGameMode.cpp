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

	State.ChangeState("Title");
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
	State.CreateState("Title");
	State.CreateState("Wait");

	// State Start
	State.SetStartFunction("Title", [=] 
		{
			MainCamera = GetWorld()->SpawnActor<AMainCamera>("MainCamera");
			
			FVector CameraStartPos = { 0.0f, 0.0f, -100.0f };
			FVector CameraTargetPos = { 0.0f, -360.0f, -100.0f };
			MainCamera->SetLerpMovePos(CameraStartPos, CameraTargetPos);

			Screen = GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");
		}
	);

	State.SetStartFunction("Wait", [=] {});

	// State Update
	State.SetUpdateFunction("Title", [=] (float _DeltaTime)
		{
			MainCamera->LerpMoveUpdate(_DeltaTime, EnterTitleTimeWeight);
			EnterTitleTimeWeight -= 2.0f * _DeltaTime;

			if (false == MainCamera->IsLerpMove())
			{
				Menu = GetWorld()->SpawnActor<ATitleMenu>("TitleMenu");
				State.ChangeState("Wait");
				return;
			}
		}
	);

	State.SetUpdateFunction("Wait", [=](float _DeltaTime) {});
}

void ATitleGameMode::InputCheck(int _Input)
{
	switch (_Input)
	{
	case 0:
		break;
	case 4:
		GEngine->EngineWindow.Off();
		break;
	default:
		break;
	}
}

