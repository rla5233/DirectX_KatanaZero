#include "PreCompile.h"
#include "Factory_004.h"

#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"

AFactory_004::AFactory_004()
{
}

AFactory_004::~AFactory_004()
{
}

void AFactory_004::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_004::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFactory_004::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GetWorld()->GetMainCamera()->SetActorLocation({ 665.0f, 395.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap4, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background4, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	Player->SetActorLocation({ 175.0f, 250.0f, 0.0f });
}

void AFactory_004::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

}

void AFactory_004::ChangeStage()
{
	Super::ChangeStage();

	GEngine->ChangeLevel("Factory_005");
}

void AFactory_004::ResetPlayer()
{
	if (UEngineInput::IsDown('R'))
	{
		Player->SetActorLocation({ 175.0f, 250.0f, 0.0f });
	}
}