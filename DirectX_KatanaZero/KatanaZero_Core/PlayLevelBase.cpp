#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "RecMapCompoBase.h"
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

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->Destroy();
		AllRecComponent[i] = nullptr;
	}

	Aim = nullptr;
	ColMap = nullptr;
	Player = nullptr;
	HUD = nullptr;

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

// ����� ����
void APlayLevelBase::Debug()
{
	DebugMessageFunction();
	ResetPlayer();
	RestartCheck();
}

// �����
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
}

// ���� �ʱ�ȭ
void APlayLevelBase::StateInit()
{
	// State ����
	State.CreateState("Play");
	State.CreateState("Replay");

	// State Start �Լ� ����
	State.SetStartFunction("Play", [=] {});
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

			InputOn();
		}
	);

	// State Update �Լ� ����
	State.SetUpdateFunction("Play", [=](float)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
			if (true == IsStageClear())
			{
				State.ChangeState("Replay");
				return;
			}
		}
	);

	State.SetUpdateFunction("Replay", std::bind(&APlayLevelBase::Replay, this, std::placeholders::_1));

	// State End �Լ� ����
}

void APlayLevelBase::Replay(float _DeltaTime)
{
	if (true)
	{
		MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());





		if (true == IsDown(VK_LBUTTON))
		{
			InputOff();

			ChangeStage();
		}
	}
}