#include "PreCompile.h"
#include "Factory_003.h"

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

	GetWorld()->GetMainCamera()->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap3, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background3, 1.0f, true);

	Player->SetActorLocation({ 175.0f, 300.0f, 0.0f });
}

void AFactory_003::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsStageClear())
	{
		GEngine->ChangeLevel("Factory_004");
	}
}

void AFactory_003::ResetPlayer()
{
	if (UEngineInput::IsDown('R'))
	{
		Player->SetActorLocation({ 175.0f, 300.0f, 0.0f });
	}
}
