#include "PreCompile.h"
#include "Factory_004.h"

#include "BackGroundObject.h"

AFactory_004::AFactory_004()
{
}

AFactory_004::~AFactory_004()
{
}

void AFactory_004::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ -300.0f, -300.0f, -100.0f });

	std::shared_ptr<ABackGroundObject> BackGround = GetWorld()->SpawnActor<ABackGroundObject>("BackGround");
	BackGround->SetSprite(ImgRes::factory_background4);
	BackGround->SetSpriteScale({ 1950.0f, 1400.0f, 1.0f });
	BackGround->SetSpriteOrder(ERenderOrder::BackGround);
}

void AFactory_004::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
