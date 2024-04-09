#include "PreCompile.h"
#include "Factory_001.h"

#include "BackGroundObject.h"

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
}

void AFactory_001::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
