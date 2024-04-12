#include "PreCompile.h"
#include "Factory_001.h"

#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "MouseAim.h"
#include "Up_HUD.h"

AFactory_001::AFactory_001()
{
}

AFactory_001::~AFactory_001()
{
}

void AFactory_001::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	std::shared_ptr<AColMapObject> ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	ColMap->SetColMapSprite(ImgRes::factory_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background2, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");

	HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");
}

void AFactory_001::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Debug();	
}

void AFactory_001::Debug()
{
	DebugMessageFunction();

	if (UEngineInput::IsDown('R'))
	{
		Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });
	}
}

void AFactory_001::DebugMessageFunction()
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
		std::string Msg = std::format("AimPos : {}\n", Aim->GetActorLocation().ToString());
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
}
