#include "PreCompile.h"
#include "Factory_001.h"

#include "ColMapObject.h"
#include "DefaultPlayer.h"
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
	HUD->CameraEffectOff();

	ColMap->SetColMapSprite(ImgRes::factory_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background2, 1.0f, true);

	Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });
}

void AFactory_001::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
