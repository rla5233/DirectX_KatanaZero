#include "PreCompile.h"
#include "Factory_001.h"

#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "MouseAim.h"

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
}

void AFactory_001::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DebugMessageFunction();
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
}
