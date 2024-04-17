#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "CameraManager.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "EnemyBase.h"
#include "MouseAim.h"
#include "Up_HUD.h"

APlayLevelBase::APlayLevelBase()
{
}

APlayLevelBase::~APlayLevelBase()
{
}

void APlayLevelBase::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void APlayLevelBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");
	ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");

	State.ChangeState("Play");
}

void APlayLevelBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Aim->Destroy();
	ColMap->Destroy();
	Player->Destroy();
	HUD->Destroy();

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->Destroy();
		AllEnemy[i] = nullptr;
	}

	Aim = nullptr;
	ColMap = nullptr;
	Player = nullptr;
	HUD = nullptr;

	AllEnemy.clear();
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
		std::string Msg = std::format("IsOnGround : {}\n", Player->IsOnGround());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnPlatForm : {}\n", Player->IsOnPlatForm());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnStairs : {}\n", Player->IsOnStairs());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnGP_Boundary : {}\n", Player->IsOnGP_Boundary());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsStairsUp : {}\n", Player->IsStairUp());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

// 상태 초기화
void APlayLevelBase::StateInit()
{
	// State 생성
	State.CreateState("Play");
	State.CreateState("Replay");

	// State Start 함수 세팅
	State.SetStartFunction("Play", [=] {});
	State.SetStartFunction("Replay", [=] 
		{ 
			Player->StateChange("Replay");
			InputOn();
		}
	);

	// State Update 함수 세팅
	State.SetUpdateFunction("Play", [=](float)
		{
			UCameraManager::PlayLevelChaseActor(GetWorld()->GetMainCamera(), ColMap->GetMapTex(), Player->GetActorLocation());
			if (true == IsStageClear())
			{
				State.ChangeState("Replay");
				return;
			}
		}
	);

	State.SetUpdateFunction("Replay", std::bind(&APlayLevelBase::Replay, this, std::placeholders::_1));

	// State End 함수 세팅
}

void APlayLevelBase::Replay(float _DeltaTime)
{
	if (true)
	{
		UCameraManager::PlayLevelChaseActor(GetWorld()->GetMainCamera(), ColMap->GetMapTex(), Player->GetActorLocation());





		if (true == IsDown(VK_LBUTTON))
		{
			InputOff();

			ChangeStage();
		}
	}
}