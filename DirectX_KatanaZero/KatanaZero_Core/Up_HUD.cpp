#include "PreCompile.h"
#include "Up_HUD.h"

AUp_HUD::AUp_HUD()
{
	Battery = CreateDefaultSubObject<USpriteRenderer>("Up_HUD_Bar");
	Timer	= CreateDefaultSubObject<USpriteRenderer>("Up_HUD_Bar");
	Bar		= CreateDefaultSubObject<USpriteRenderer>("Up_HUD_Bar");
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
	Timer->SetSprite(ImgRes::ui_up_hud_timer);
	Bar->SetSprite(ImgRes::ui_up_hud_bar);
}

void AUp_HUD::SettingRenderOrder()
{
	Battery->SetOrder(ERenderOrder::UI);
	Timer->SetOrder(ERenderOrder::UI);
	Bar->SetOrder(ERenderOrder::UI);
}

void AUp_HUD::SettingTransform()
{
	Battery->SetAutoSize(2.0f, true);
	Timer->SetAutoSize(2.0f, true);
	Bar->SetAutoSize(2.0f, true);

	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	Battery->Transform.SetPosition({ CameraPos.X - 561.0f, CameraPos.Y + 337.0f, 0.0f });
	Timer->Transform.SetPosition({ CameraPos.X - 10.0f, CameraPos.Y + 339.0f, 0.0f });
	Bar->Transform.SetPosition({ CameraPos.X, CameraPos.Y + 337.0f, 0.0f });
}

void AUp_HUD::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

