#include "PreCompile.h"
#include "Up_HUD.h"

AUp_HUD::AUp_HUD()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	// Left
	Battery_Part.reserve(11);
	for (size_t i = 0; i < Battery_Part.capacity(); i++)
	{
		Battery_Part.push_back(CreateDefaultSubObject<USpriteRenderer>("HUD_Battery_Part"));
		Battery_Part[i]->SetupAttachment(Root);
	}

	Battery		= CreateDefaultSubObject<USpriteRenderer>("HUD_Battery");
	Shift		= CreateDefaultSubObject<USpriteRenderer>("HUD_Shift");
	
	Battery->SetupAttachment(Root);
	Shift->SetupAttachment(Root);

	// Mid
	Timer_Bar	= CreateDefaultSubObject<USpriteRenderer>("HUD_Timer_Bar");
	Timer		= CreateDefaultSubObject<USpriteRenderer>("HUD_Timer");
	
	Timer_Bar->SetupAttachment(Root);
	Timer->SetupAttachment(Root);

	// Right
	R_ClickIcon = CreateDefaultSubObject<USpriteRenderer>("R_Click_Icon");
	L_ClickIcon = CreateDefaultSubObject<USpriteRenderer>("L_Click_Icon");
	ItemIcon	= CreateDefaultSubObject<USpriteRenderer>("Item_Icon");
	KatanaIcon	= CreateDefaultSubObject<USpriteRenderer>("Katana_Icon");
	Weapon		= CreateDefaultSubObject<USpriteRenderer>("HUD_Weapon");
	
	R_ClickIcon->SetupAttachment(Root);
	L_ClickIcon->SetupAttachment(Root);
	ItemIcon->SetupAttachment(Root);
	KatanaIcon->SetupAttachment(Root);
	Weapon->SetupAttachment(Root);

	// BackGround
	Bar			= CreateDefaultSubObject<USpriteRenderer>("HUD_Bar");
	Bar->SetupAttachment(Root);

	SetRoot(Root);
}

AUp_HUD::~AUp_HUD()
{
}

void AUp_HUD::BeginPlay()
{
	Super::BeginPlay();

	SettingSprite();
	SettingRenderOrder();
	SettingTransform();

	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	SetActorLocation({ CameraPos.X, CameraPos.Y + 337.0f, 0.0f });
}

void AUp_HUD::SettingSprite()
{
	// Left
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetSprite(ImgRes::ui_up_hud_battery_part);
	}

	Battery->SetSprite(ImgRes::ui_up_hud_battery);
	Shift->SetSprite(ImgRes::ui_shift_up);

	// Mid
	Timer_Bar->SetSprite(ImgRes::ui_up_hud_timer_bar);
	Timer->SetSprite(ImgRes::ui_up_hud_timer);
	
	// Right
	R_ClickIcon->SetSprite(ImgRes::ui_right_click);
	L_ClickIcon->SetSprite(ImgRes::ui_left_click);
	ItemIcon->SetSprite(ImgRes::ui_item_icon);
	KatanaIcon->SetSprite(ImgRes::ui_katana_icon);
	Weapon->SetSprite(ImgRes::ui_up_hud_weapon);

	// BackGround
	Bar->SetSprite(ImgRes::ui_up_hud_bar);
}

void AUp_HUD::SettingRenderOrder()
{
	// Left
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetOrder(ERenderOrder::UI);
	}

	Battery->SetOrder(ERenderOrder::UI);
	Shift->SetOrder(ERenderOrder::UI);

	// Mid
	Timer_Bar->SetOrder(ERenderOrder::UI);
	Timer->SetOrder(ERenderOrder::UI);
	
	// Right
	R_ClickIcon->SetOrder(ERenderOrder::UI);
	L_ClickIcon->SetOrder(ERenderOrder::UI);
	ItemIcon->SetOrder(ERenderOrder::UI);
	KatanaIcon->SetOrder(ERenderOrder::UI);
	Weapon->SetOrder(ERenderOrder::UI);

	// BackGround
	Bar->SetOrder(ERenderOrder::UI);
}

void AUp_HUD::SettingTransform()
{
	// Left
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetAutoSize(2.0f, true);
	}

	Battery->SetAutoSize(2.0f, true);
	Shift->SetAutoSize(2.0f, true);

	// Mid
	Timer_Bar->SetAutoSize(2.0f, true);
	Timer->SetAutoSize(2.0f, true);
	
	// Right
	R_ClickIcon->SetAutoSize(2.0f, true);
	L_ClickIcon->SetAutoSize(2.0f, true);
	ItemIcon->SetAutoSize(2.0f, true);
	KatanaIcon->SetAutoSize(2.0f, true);
	Weapon->SetAutoSize(2.0f, true);

	// BackGround
	Bar->SetAutoSize(2.0f, true);
	

	// Left
	const float interval = 10.0f;
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		float inter = interval * static_cast<float>(i);
		Battery_Part[i]->SetPosition({ -612.0f + inter, 1.0f, 0.0f });
	}

	Battery->SetPosition({ -561.0f, 0.0f, 0.0f });
	Shift->SetPosition({ -455.0f, 1.0f, 0.0f });
	
	// Mid
	Timer_Bar->SetPosition({ 6.0f, 6.0f, 0.0f });
	Timer->SetPosition({ -10.0f, 2.0f, 0.0f });
	
	// Right
	R_ClickIcon->SetPosition({ 616.0f, -24.0f, 0.0f });
	L_ClickIcon->SetPosition({ 553.0f, -24.0f, 0.0f });
	ItemIcon->SetPosition({ 597.0f, -2.0f, 0.0f });
	KatanaIcon->SetPosition({ 533.0f, -2.0f, 0.0f });
	Weapon->SetPosition({ 565.0f, -1.0f, 0.0f });
}

void AUp_HUD::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

