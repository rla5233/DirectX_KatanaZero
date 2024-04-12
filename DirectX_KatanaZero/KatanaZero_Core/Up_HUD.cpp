#include "PreCompile.h"
#include "Up_HUD.h"

AUp_HUD::AUp_HUD()
{
	Battery = CreateDefaultSubObject<USpriteRenderer>("HUD_Battery");
	Shift	= CreateDefaultSubObject<USpriteRenderer>("HUD_Shift");
	
	Timer	= CreateDefaultSubObject<USpriteRenderer>("HUD_Timer");

	Weapon  = CreateDefaultSubObject<USpriteRenderer>("HUD_Weapon");

	Bar		= CreateDefaultSubObject<USpriteRenderer>("HUD_Bar");
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
	Battery->SetSprite(ImgRes::ui_up_hud_battery);
	Shift->SetSprite(ImgRes::ui_shift_up);

	Timer->SetSprite(ImgRes::ui_up_hud_timer);
	
	Weapon->SetSprite(ImgRes::ui_up_hud_weapon);

	Bar->SetSprite(ImgRes::ui_up_hud_bar);
}

void AUp_HUD::SettingRenderOrder()
{
	Battery->SetOrder(ERenderOrder::UI);
	Shift->SetOrder(ERenderOrder::UI);

	Timer->SetOrder(ERenderOrder::UI);
	
	Weapon->SetOrder(ERenderOrder::UI);

	Bar->SetOrder(ERenderOrder::UI);
}

void AUp_HUD::SettingTransform()
{
	Battery->SetAutoSize(2.0f, true);
	Shift->SetAutoSize(2.0f, true);
	Timer->SetAutoSize(2.0f, true);
	Weapon->SetAutoSize(2.0f, true);
	Bar->SetAutoSize(2.0f, true);

	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	Battery->Transform.SetPosition({ CameraPos.X - 561.0f, CameraPos.Y + 337.0f, 0.0f });
	Shift->Transform.SetPosition({ CameraPos.X - 455.0f, CameraPos.Y + 338.0f, 0.0f });
	Timer->Transform.SetPosition({ CameraPos.X - 10.0f, CameraPos.Y + 339.0f, 0.0f });
	Weapon->Transform.SetPosition({ CameraPos.X + 565.0f, CameraPos.Y + 336.0f, 0.0f });
	Bar->Transform.SetPosition({ CameraPos.X, CameraPos.Y + 337.0f, 0.0f });
}

void AUp_HUD::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

