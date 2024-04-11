#include "PreCompile.h"
#include "TitleScreen.h"

#include "Constant.h"

ATitleScreen::ATitleScreen()
{
	BackGround	= CreateDefaultSubObject<USpriteRenderer>("BackGround");
	Fence		= CreateDefaultSubObject<USpriteRenderer>("Fence");
	Plants		= CreateDefaultSubObject<USpriteRenderer>("Plants");
	Grass		= CreateDefaultSubObject<USpriteRenderer>("Grass");
}

ATitleScreen::~ATitleScreen()
{
} 

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	// Sprite Settimg
	BackGround->SetSprite(ImgRes::title_background);
	Fence->SetSprite(ImgRes::title_fence);
	Plants->SetSprite(ImgRes::title_plant);
	Grass->SetSprite(ImgRes::title_grass);

	// RenderOrder Setting
	BackGround->SetOrder(ETitleRenderOrder::BackGround);
	Fence->SetOrder(ETitleRenderOrder::Mid);
	Plants->SetOrder(ETitleRenderOrder::Top);
	Grass->SetOrder(ETitleRenderOrder::Top);

	// Transform Setting
	BackGround->Transform.SetScale({ 1280.0f, 1440.0f, 1.0f });
	Fence->Transform.SetScale({ 1280.0f, 1440.0f, 1.0f });
	Plants->Transform.SetScale({ 1280.0f, 510.0f, 1.0f });
	Plants->Transform.SetPosition({ 0.0f, -465.0f, 0.0f });
	Grass->Transform.SetScale({ 1280.0f, 240.0f, 1.0f });
	Grass->Transform.SetPosition({ 0.0f, -650.0f, 0.0f });

	// Anim
	Plants->CreateAnimation(Anim::plants, ImgRes::title_plant, 0.1f, true);
	Plants->ChangeAnimation(Anim::plants);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}