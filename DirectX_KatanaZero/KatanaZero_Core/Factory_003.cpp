#include "PreCompile.h"
#include "Factory_003.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"

AFactory_003::AFactory_003()
{
}

AFactory_003::~AFactory_003()
{
}

void AFactory_003::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_003::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFactory_003::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	
	MainCamera->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap3, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background3, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	Player->SetActorLocation({ 175.0f, 300.0f, 0.0f });
}

void AFactory_003::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFactory_003::ChangeStage()
{
	Super::ChangeStage();

	GEngine->ChangeLevel("Factory_004");
}

void AFactory_003::ResetPlayer()
{
	if (UEngineInput::IsDown('R'))
	{
		Player->SetActorLocation({ 175.0f, 300.0f, 0.0f });
	}
}
