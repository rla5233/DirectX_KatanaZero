#include "PreCompile.h"
#include "HeadHunter_Phase1.h"

#include "BackGroundObject.h"

AHeadHunter_Phase1::AHeadHunter_Phase1()
{
}

AHeadHunter_Phase1::~AHeadHunter_Phase1()
{
}

void AHeadHunter_Phase1::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -100.0f });
	
	std::shared_ptr<ABackGroundObject> BackGround = GetWorld()->SpawnActor<ABackGroundObject>("BackGround");
	BackGround->SetSprite(ImgRes::headhunter_background1);
	BackGround->SetSpriteScale({ 1280.0f, 720.0f, 1.0f });
}

void AHeadHunter_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
