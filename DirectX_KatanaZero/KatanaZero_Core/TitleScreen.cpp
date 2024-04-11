#include "PreCompile.h"
#include "TitleScreen.h"

#include "Constant.h"

ATitleScreen::ATitleScreen()
{
	BackGround	= CreateDefaultSubObject<USpriteRenderer>("BackGround");
	Fence		= CreateDefaultSubObject<USpriteRenderer>("Fence");
	Plants		= CreateDefaultSubObject<USpriteRenderer>("Plants");
	Grass		= CreateDefaultSubObject<USpriteRenderer>("Grass");

	Neon_ZER	= CreateDefaultSubObject<USpriteRenderer>("Neon_ZER");
	Neon_O		= CreateDefaultSubObject<USpriteRenderer>("Neon_O");
	Neon_Katana = CreateDefaultSubObject<USpriteRenderer>("Neon_Katana");
}

ATitleScreen::~ATitleScreen()
{
} 

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SettingSprite();
	SettingRenderOrder();
	SettingTransform();

	// Anim
	Plants->CreateAnimation(Anim::plants, ImgRes::title_plant, 0.1f, true);
	Plants->ChangeAnimation(Anim::plants);
}

void ATitleScreen::SettingSprite()
{
	BackGround->SetSprite(ImgRes::title_background);
	Fence->SetSprite(ImgRes::title_fence);
	Plants->SetSprite(ImgRes::title_plant);
	Grass->SetSprite(ImgRes::title_grass);

	Neon_ZER->SetSprite(ImgRes::title_neon_zer);
	Neon_O->SetSprite(ImgRes::title_neon_o);
	Neon_Katana->SetSprite(ImgRes::title_neon_katana);
}

void ATitleScreen::SettingRenderOrder()
{
	BackGround->SetOrder(ETitleRenderOrder::BackGround);
	Fence->SetOrder(ETitleRenderOrder::Mid);
	Plants->SetOrder(ETitleRenderOrder::Top);
	Grass->SetOrder(ETitleRenderOrder::Top);

	Neon_ZER->SetOrder(ETitleRenderOrder::Mid);
	Neon_O->SetOrder(ETitleRenderOrder::Mid);
	Neon_Katana->SetOrder(ETitleRenderOrder::Top);
}

void ATitleScreen::SettingTransform()
{
	BackGround->SetAutoSize(2.0f, true);
	Fence->SetAutoSize(2.0f, true);
	Plants->SetAutoSize(2.0f, true);
	Grass->SetAutoSize(2.0f, true);
	Neon_ZER->SetAutoSize(1.25f, true);
	Neon_O->SetAutoSize(1.25f, true);
	Neon_Katana->SetAutoSize(1.5f, true);

	Plants->Transform.SetPosition({ 0.0f, -465.0f, 0.0f });
	Grass->Transform.SetPosition({ 0.0f, -650.0f, 0.0f });
	Neon_ZER->Transform.SetPosition({ 0.0f, -300.0f, 0.0f });
	Neon_O->Transform.SetPosition({ 0.0f, -300.0f, 0.0f });
	Neon_Katana->Transform.SetPosition({ 0.0f, -240.0f, 0.0f });
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}