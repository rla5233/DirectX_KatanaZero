#include "PreCompile.h"
#include "TitleScreen.h"

#include "Constant.h"

ATitleScreen::ATitleScreen()
{
	Plants		= CreateDefaultSubObject<USpriteRenderer>("Plants");
	Fence		= CreateDefaultSubObject<USpriteRenderer>("Fence");
	BackGround	= CreateDefaultSubObject<USpriteRenderer>("BackGround");
}

ATitleScreen::~ATitleScreen()
{
} 

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	Plants->SetSprite(ImgRes::title_plant);
	Fence->SetSprite(ImgRes::title_fence);
	BackGround->SetSprite(ImgRes::title_background);

	BackGround->Transform.SetScale({ 1280.0f, 1440.0f, 1.0f });
	Fence->Transform.SetScale({ 1280.0f, 1440.0f, 1.0f });
	Plants->Transform.SetScale({ 1280.0f, 510.0f, 1.0f });
	Plants->Transform.SetPosition({ 0.0f, -465.0f, 0.0f });

	Plants->CreateAnimation(Anim::plants, ImgRes::title_plant, 0.1f, true);
	Plants->ChangeAnimation(Anim::plants);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}