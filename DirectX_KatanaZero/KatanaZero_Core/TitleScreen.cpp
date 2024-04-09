#include "PreCompile.h"
#include "TitleScreen.h"

#include "Constant.h"

ATitleScreen::ATitleScreen()
{
	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");

	BackGround->SetSprite(ImgRes::title_background);
}

ATitleScreen::~ATitleScreen()
{
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, 0.0f, 0.0f });
	SetActorScale3D({ 1280.0f, 720.0f, 1.0f });

	BackGround->Transform.SetScale({ 1280.0f, 720.0f, 1.0f });

}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
