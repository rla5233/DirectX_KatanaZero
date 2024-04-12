#include "PreCompile.h"
#include "Up_HUD.h"

AUp_HUD::AUp_HUD()
{
	// Left
	Battery		= CreateDefaultSubObject<USpriteRenderer>("HUD_Battery");
	Shift		= CreateDefaultSubObject<USpriteRenderer>("HUD_Shift");
		
	// Mid
	Timer		= CreateDefaultSubObject<USpriteRenderer>("HUD_Timer");

	// Right
	R_ClickIcon = CreateDefaultSubObject<USpriteRenderer>("R_Click_Icon");
	L_ClickIcon = CreateDefaultSubObject<USpriteRenderer>("L_Click_Icon");
	ItemIcon	= CreateDefaultSubObject<USpriteRenderer>("Item_Icon");
	KatanaIcon	= CreateDefaultSubObject<USpriteRenderer>("Katana_Icon");
	Weapon		= CreateDefaultSubObject<USpriteRenderer>("HUD_Weapon");

	// BackGround
	Bar			= CreateDefaultSubObject<USpriteRenderer>("HUD_Bar");
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
}

void AUp_HUD::SettingSprite()
{
	// Left
	Battery->SetSprite(ImgRes::ui_up_hud_battery);
	Shift->SetSprite(ImgRes::ui_shift_up);

	// Mid
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
	Battery->SetOrder(ERenderOrder::UI);
	Shift->SetOrder(ERenderOrder::UI);

	// Mid
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
	Battery->SetAutoSize(2.0f, true);
	Shift->SetAutoSize(2.0f, true);

	// Mid
	Timer->SetAutoSize(2.0f, true);
	
	// Right
	R_ClickIcon->SetAutoSize(2.0f, true);
	L_ClickIcon->SetAutoSize(2.0f, true);
	ItemIcon->SetAutoSize(2.0f, true);
	KatanaIcon->SetAutoSize(2.0f, true);
	Weapon->SetAutoSize(2.0f, true);

	// BackGround
	Bar->SetAutoSize(2.0f, true);
	

	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	
	// Left
	Battery->Transform.SetPosition({ CameraPos.X - 561.0f, CameraPos.Y + 337.0f, 0.0f });
	Shift->Transform.SetPosition({ CameraPos.X - 455.0f, CameraPos.Y + 338.0f, 0.0f });
	
	// Mid
	Timer->Transform.SetPosition({ CameraPos.X - 10.0f, CameraPos.Y + 339.0f, 0.0f });
	
	// Right
	R_ClickIcon->Transform.SetPosition({ CameraPos.X + 616.0f, CameraPos.Y + 313.0f, 0.0f });
	L_ClickIcon->Transform.SetPosition({ CameraPos.X + 553.0f, CameraPos.Y + 313.0f, 0.0f });
	ItemIcon->Transform.SetPosition({ CameraPos.X + 597.0f, CameraPos.Y + 335.0f, 0.0f });
	KatanaIcon->Transform.SetPosition({ CameraPos.X + 533.0f, CameraPos.Y + 335.0f, 0.0f });
	Weapon->Transform.SetPosition({ CameraPos.X + 565.0f, CameraPos.Y + 336.0f, 0.0f });
	
	// BackGround
	Bar->Transform.SetPosition({ CameraPos.X, CameraPos.Y + 337.0f, 0.0f });
}

void AUp_HUD::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
