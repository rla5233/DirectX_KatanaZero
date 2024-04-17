#include "PreCompile.h"
#include "Factory_005.h"

#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"

AFactory_005::AFactory_005()
{
}

AFactory_005::~AFactory_005()
{
}

void AFactory_005::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_005::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFactory_005::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GetWorld()->GetMainCamera()->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap5, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background5, 1.0f, true);

	Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });
}

void AFactory_005::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFactory_005::ResetPlayer()
{
	if (UEngineInput::IsDown('R'))
	{
		Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });
	}
}
