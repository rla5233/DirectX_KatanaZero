#include "PreCompile.h"
#include "HeadHunter_Phase2.h"

#include "BackGroundObject.h"

AHeadHunter_Phase2::AHeadHunter_Phase2()
{
}

AHeadHunter_Phase2::~AHeadHunter_Phase2()
{
}

void AHeadHunter_Phase2::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f,0.0f,-100.0f });

	std::shared_ptr<ABackGroundObject> BackGround = GetWorld()->SpawnActor<ABackGroundObject>("BackGround");
	BackGround->SetSprite(ImgRes::headhunter_background2);
	BackGround->SetSpriteScale({ 1280.0f, 720.0f, 1.0f });
	BackGround->SetSpriteOrder(ERenderOrder::BackGround);
}

void AHeadHunter_Phase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
