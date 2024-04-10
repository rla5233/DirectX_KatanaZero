#include "PreCompile.h"
#include "Factory_001.h"

#include "BackGroundObject.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"

AFactory_001::AFactory_001()
{
}

AFactory_001::~AFactory_001()
{
}

void AFactory_001::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ -235.0f, 0.0f, -100.0f });

	std::shared_ptr<ABackGroundObject> BackGround = GetWorld()->SpawnActor<ABackGroundObject>("BackGround");
	BackGround->SetSprite(ImgRes::factory_background2);
	BackGround->SetSpriteScale({ 1800.0f, 784.0f, 1.0f });

	std::shared_ptr<AColMapObject> ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	ColMap->SetSprite(ImgRes::factory_colmap2);
	ColMap->SetSpriteScale({ 1800.0f, 784.0f, 1.0f });

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	Player->SetActorLocation({ -725.0f, -245.0f, 0.0f });
}

void AFactory_001::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
