#include "PreCompile.h"
#include "Factory_005.h"

#include "BackGroundObject.h"

AFactory_005::AFactory_005()
{
}

AFactory_005::~AFactory_005()
{
}

void AFactory_005::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ -450.0f, -150.0f, -100.0f });
	
	std::shared_ptr<ABackGroundObject> BackGround = GetWorld()->SpawnActor<ABackGroundObject>("BackGround");
	BackGround->SetSprite(ImgRes::factory_background5);
	BackGround->SetSpriteScale({ 2240.0f, 1088.0f, 1.0f });
	BackGround->SetSpriteOrder(ERenderOrder::BackGround);
}

void AFactory_005::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
