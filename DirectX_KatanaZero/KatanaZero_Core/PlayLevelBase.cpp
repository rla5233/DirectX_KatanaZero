#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "CameraManager.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
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

	std::shared_ptr<AMouseAim> Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");
	ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");
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

	PlayerPos.Y = MapTexScale.Y - PlayerPos.Y;

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
}

void APlayLevelBase::DebugMessageFunction()
{
	{
		std::string Msg = std::format("WinScale : {}\n", GEngine->EngineWindow.GetWindowScale().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("AimPos : {}\n", AMouseAim::GetMouseAimLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

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
