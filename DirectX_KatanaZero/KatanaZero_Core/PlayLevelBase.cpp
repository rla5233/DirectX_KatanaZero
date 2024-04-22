#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "RecMapCompoBase.h"
#include "DefaultPlayer.h"
#include "EnemyBase.h"
#include "MouseAim.h"
#include "ReplayUI.h"
#include "Up_HUD.h"
#include "Go.h"

#include "GrayScaleEffect.h"

APlayLevelBase::APlayLevelBase()
{
}

APlayLevelBase::~APlayLevelBase()
{
}

void APlayLevelBase::BeginPlay()
{
	Super::BeginPlay();

	USpawnManager::SetGameMode(this);

	StateInit();
}

void APlayLevelBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	MainCamera = GetWorld()->SpawnActor<AMainCamera>("MainCamera");

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");
	ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");

	State.ChangeState("Intro");
}

void APlayLevelBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Aim->Destroy();
	ColMap->Destroy();
	Player->Destroy();
	HUD->Destroy();

	if (nullptr != Go)
	{
		Go->Destroy();
	}

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->Destroy();
		AllEnemy[i] = nullptr;
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->Destroy();
		AllRecComponent[i] = nullptr;
	}

	Aim = nullptr;
	ColMap = nullptr;
	Player = nullptr;
	HUD = nullptr;
	Go = nullptr;

	AllEnemy.clear();
	AllRecComponent.clear();
}

void APlayLevelBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	Debug();
}

bool APlayLevelBase::IsStageClear()
{
	bool Result = false;

	if (0 == TotalEnemy)
	{
		Result = true;
	}

	return Result;
}

bool APlayLevelBase::IsRelayStart()
{
	bool Result = false;

	std::shared_ptr<UEngineTexture> MapTex = ColMap->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector PlayerPos = Player->GetActorLocation();

	PlayerPos.Y = MapTexScale.Y - (PlayerPos.Y + 5.0f);

	Color8Bit PixelColor = MapTex->GetColor(PlayerPos, Color8Bit::Black);

	if (ColMap::RED == PixelColor)
	{
		Result = true;
	}

	return Result;
}

// 디버깅 관련
void APlayLevelBase::Debug()
{
	DebugMessageFunction();
	ResetPlayer();
	RestartCheck();
}

// 재시작
void APlayLevelBase::RestartCheck()
{
	if (UEngineInput::IsDown('P'))
	{
		LevelEnd(nullptr);
		LevelStart(nullptr);
	}
}

void APlayLevelBase::DebugMessageFunction()
{
	{
		std::string Msg = std::format("Player_Pos : {}\n", Player->GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player_State : {}\n", Player->GetCurState());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnGround : {}\n", Player->IsOnGround(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnPlatForm : {}\n", Player->IsOnPlatForm(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnStairs : {}\n", Player->IsOnStairs(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnGP_Boundary : {}\n", Player->IsOnGP_Boundary(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("ReplaySpeed : {}\n", Player->GetReplaySpeed());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

// 상태 초기화
void APlayLevelBase::StateInit()
{
	// State 생성
	State.CreateState("Intro");
	State.CreateState("Play");
	State.CreateState("Clear");
	State.CreateState("Replay");

	// State Start 함수 세팅
	State.SetStartFunction("Intro", [=] {});
	State.SetStartFunction("Play", [=] 
		{
			Player->SetRecordingActive(true);

			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->SetRecordingActive(true);
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->SetRecordingActive(true);
			}
		}
	);

	State.SetStartFunction("Clear", std::bind(&APlayLevelBase::ClearStart, this));
	State.SetStartFunction("Replay", [=] 
		{ 
			Player->StateChange("Replay");

			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->StateChange("Replay");
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->StateChange("Replay");
			}

			Go->StateChange("Replay");
			HUD->StateChange("Replay");

			InputOn();

			GetWorld()->GetLastTarget()->AddEffect<UGrayScaleEffect>();
			ReplayUI = GetWorld()->SpawnActor<AReplayUI>("Replay_UI");
		}
	);

	// State Update 함수 세팅
	State.SetUpdateFunction("Intro", [=](float _DeltaTime) { State.ChangeState("Play"); });
	State.SetUpdateFunction("Play", [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
			if (true == IsStageClear())
			{
				State.ChangeState("Clear");
				return;
			}
		}
	);

	State.SetUpdateFunction("Clear", [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
			if (true == IsRelayStart())
			{
				State.ChangeState("Replay");
				return;
			}
		}
	);

	State.SetUpdateFunction("Replay", [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());

			if (true == IsDown(VK_RBUTTON))
			{
				InputOff();

				ChangeStage();
			}
		}
	);

	// State End 함수 세팅
	State.SetEndFunction("Clear", [=]
		{
			Player->SetRecordingActive(false);

			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->SetRecordingActive(false);
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->SetRecordingActive(false);
			}
		}
	);
}

void APlayLevelBase::ClearStart()
{
	Go = GetWorld()->SpawnActor<AGo>("Go");
}

void APlayLevelBase::Replay(float _DeltaTime)
{

}

void APlayLevelBase::SetReplay()
{
	ResetReplaySpeed();

	Player->SetReplayMode(EReplayMode::Play);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Play);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Play);
	}
}

void APlayLevelBase::SetReplayStop()
{
	Player->SetReplayMode(EReplayMode::Stop);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Stop);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Stop);
	}
}

void APlayLevelBase::SetRewind()
{
	ResetReplaySpeed();

	Player->SetReplayMode(EReplayMode::Rewind);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Rewind);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Rewind);
	}
}

void APlayLevelBase::ResetReplaySpeed()
{
	Player->SetReplaySpeed(1);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplaySpeed(1);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplaySpeed(1);
	}
}

void APlayLevelBase::IncreaseReplaySpeed()
{
	Player->IncreaseReplaySpeed();

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->IncreaseReplaySpeed();
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->IncreaseReplaySpeed();
	}
}

bool APlayLevelBase::IsReplayEnd() const
{
	return Player->IsReplayEnd();
}

bool APlayLevelBase::IsRewindEnd() const
{
	return Player->IsRewindEnd();
}


