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
}

void APlayLevelBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");
	ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");
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

	UCameraManager::PlayLevelChaseActor(GetWorld()->GetMainCamera(), ColMap->GetMapTex(), Player->GetActorLocation());
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

void APlayLevelBase::Debug()
{
	DebugMessageFunction();
	ResetPlayer();
	RestartCheck();
}

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
	//{
	//	std::string Msg = std::format("WinScale : {}\n", GEngine->EngineWindow.GetWindowScale().ToString());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	//{
	//	std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	//{
	//	std::string Msg = std::format("AimPos : {}\n", AMouseAim::GetMouseAimLocation().ToString());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

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