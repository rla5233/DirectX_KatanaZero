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

	ULerpObject::SetActor(this);

	SettingSprite();
	SettingRenderOrder();
	SettingTransform();

	StateInit();

	State.ChangeState("TitleEnter");
}

void ATitleMenu::SettingSprite()
{
	Text->SetSprite(ImgRes::title_menu_text);
	BlackBar->SetSprite(ImgRes::title_menu_black_bar);
	WhiteBar->SetSprite(ImgRes::title_menu_white_bar);

	//BlackBar->SetPlusColor({ 0.0f, 0.0f, 0.0f, 255.0f });
	//BlackBar->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	//BlackBar->SetAlpha(0.0f);
}

void ATitleMenu::SettingRenderOrder()
{
	Text->SetOrder(ETitleRenderOrder::Text);
	WhiteBar->SetOrder(ETitleRenderOrder::Text);
	BlackBar->SetOrder(ETitleRenderOrder::Text);
}

void ATitleMenu::SettingTransform()
{
	Text->SetAutoSize(1.0f, true);

	BlackBar->SetScale({ 523.0f, 240.0f, 1.0f });
	WhiteBar->SetScale({ 500.0f, 35.0f, 1.0f });

	WhiteBar->SetPosition({ 0.0f, 75.0f, 0.0f });
}

void ATitleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ATitleMenu::StateInit()
{
	// State Create
	State.CreateState("TitleEnter");

	// State Start
	State.SetStartFunction("TitleEnter", [=] 
		{
			FVector StartPos = { 0.0f, -800.0f, 0.0f };
			FVector TargetPos = { 0.0f, -520.0f, 0.0f };
			SetLerpMovePos(StartPos, TargetPos);
		}
	);

	// State Update
	State.SetUpdateFunction("TitleEnter", [=] (float _DeltaTime)
		{
			LerpMoveUpdate(_DeltaTime, EnterTitleTimeWeight);
			EnterTitleTimeWeight -= 4.5f * _DeltaTime;
		}
	);
}

