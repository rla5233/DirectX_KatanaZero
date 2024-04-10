#include "PreCompile.h"
#include "Factory_001.h"

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

	std::shared_ptr<AColMapObject> ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");
	ColMap->SetColMapSprite(ImgRes::factory_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background2, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player");
	Player->SetActorLocation({ -725.0f, -245.0f, 0.0f });
}

void AFactory_001::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
