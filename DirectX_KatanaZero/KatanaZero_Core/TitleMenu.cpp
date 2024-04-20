#include "PreCompile.h"
#include "TitleMenu.h"

ATitleMenu::ATitleMenu()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	
	Text = CreateDefaultSubObject<USpriteRenderer>("Text");
	BlackBar = CreateDefaultSubObject<USpriteRenderer>("BlackBar");
	WhiteBar = CreateDefaultSubObject<USpriteRenderer>("WhiteBar");
	
	Text->SetupAttachment(Root);
	BlackBar->SetupAttachment(Root);
	WhiteBar->SetupAttachment(Root);

	SetRoot(Root);
}

ATitleMenu::~ATitleMenu()
{
}

void ATitleMenu::BeginPlay()
{
	Super::BeginPlay();

	SettingSprite();
	SettingRenderOrder();
	SettingTransform();
}

void ATitleMenu::SettingSprite()
{
	Text->SetSprite(ImgRes::title_menu_text);
	BlackBar->SetSprite(ImgRes::title_menu_black_bar);
	WhiteBar->SetSprite(ImgRes::title_menu_white_bar);
	


}

void ATitleMenu::SettingRenderOrder()
{
	Text->SetOrder(ETitleRenderOrder::Text);
	BlackBar->SetOrder(ETitleRenderOrder::Text);
	WhiteBar->SetOrder(ETitleRenderOrder::Text);

	Text->SetAutoSize(1.0f, true);
	BlackBar->SetAutoSize(1.0f, true);
	WhiteBar->SetAutoSize(1.0f, true);
}

void ATitleMenu::SettingTransform()
{
}

void ATitleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}