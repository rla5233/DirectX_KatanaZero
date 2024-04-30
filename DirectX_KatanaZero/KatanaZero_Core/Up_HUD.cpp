#include "PreCompile.h"
#include "Up_HUD.h"

#include "PlayLevelBase.h"

AUp_HUD::AUp_HUD()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
}

AUp_HUD::~AUp_HUD()
{
}

void AUp_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	CreateImage();
	SettingImage();
	SettingRenderOrder();
	SettingTransform();
	StateInit();

	State.ChangeState(HudState::play);
}

void AUp_HUD::CreateImage()
{
	// Left
	Battery_Part.reserve(11);
	for (size_t i = 0; i < Battery_Part.capacity(); i++)
	{
		Battery_Part.push_back(CreateWidget<UImage>(GetWorld(), "HUD_Battery_Part"));
	}

	Battery = CreateWidget<UImage>(GetWorld(), "HUD_Battery");
	Shift = CreateWidget<UImage>(GetWorld(), "HUD_Shift");

	// Mid
	Timer_Bar = CreateWidget<UImage>(GetWorld(), "HUD_Timer_Bar");
	Timer_Bar_Black = CreateWidget<UImage>(GetWorld(), "HUD_Timer_Bar_Black");
	Timer = CreateWidget<UImage>(GetWorld(), "HUD_Timer");

	// Right
	R_ClickIcon = CreateWidget<UImage>(GetWorld(), "R_Click_Icon");
	L_ClickIcon = CreateWidget<UImage>(GetWorld(), "L_Click_Icon");
	ItemIcon = CreateWidget<UImage>(GetWorld(), "Item_Icon");
	KatanaIcon = CreateWidget<UImage>(GetWorld(), "Katana_Icon");
	Weapon = CreateWidget<UImage>(GetWorld(), "HUD_Weapon");

	// BackGround
	Bar = CreateWidget<UImage>(GetWorld(), "HUD_Bar");
}

void AUp_HUD::SettingImage()
{
	// Left
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetSprite(ImgRes::ui_up_hud_battery_part1);
	}

	Battery->SetSprite(ImgRes::ui_up_hud_battery);
	Shift->SetSprite(ImgRes::ui_shift_up);

	// Mid
	Timer_Bar->SetSprite(ImgRes::ui_up_hud_timer_bar1);
	Timer_Bar_Black->SetSprite(ImgRes::ui_up_hud_timer_bar2);
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
		Battery_Part[i]->AddToViewPort(EWidgetOrder::Top);
	}

	Battery->AddToViewPort(EWidgetOrder::Mid);
	Shift->AddToViewPort(EWidgetOrder::Mid);

	// Mid
	Timer_Bar->AddToViewPort(EWidgetOrder::Top);
	Timer_Bar_Black->AddToViewPort(EWidgetOrder::Top);
	Timer->AddToViewPort(EWidgetOrder::Mid);
	
	// Right
	ItemIcon->AddToViewPort(EWidgetOrder::Top);
	KatanaIcon->AddToViewPort(EWidgetOrder::Top);
	R_ClickIcon->AddToViewPort(EWidgetOrder::Top);
	L_ClickIcon->AddToViewPort(EWidgetOrder::Top);
	Weapon->AddToViewPort(EWidgetOrder::Mid);

	// BackGround
	Bar->AddToViewPort(EWidgetOrder::Bottom);
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
	Timer_Bar_Black->SetScale({ 0.0f, 22.0f, 1.0f });
	
	// Right
	R_ClickIcon->SetAutoSize(2.0f, true);
	L_ClickIcon->SetAutoSize(2.0f, true);
	ItemIcon->SetAutoSize(2.0f, true);
	KatanaIcon->SetAutoSize(2.0f, true);
	Weapon->SetAutoSize(2.0f, true);

	// BackGround
	Bar->SetAutoSize(2.0f, true);
	
	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	WinScale.Y -= 47.0f;

	// Left
	const float interval = 10.0f;
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		float inter = interval * static_cast<float>(i);
		Battery_Part[i]->SetPosition({ -612.0f + inter, WinScale.hY(), 0.0f });
	}

	Battery->SetPosition({ -561.0f, WinScale.hY(), 0.0f });
	Shift->SetPosition({ -455.0f, WinScale.hY() + 1.0f, 0.0f });
	
	// Mid
	Timer_Bar->SetPosition({ 6.0f, WinScale.hY() + 5.0f, 0.0f });
	Timer_Bar_Black->SetPosition({ 100.0f, WinScale.hY() + 5.0f, 0.0f });
	Timer->SetPosition({ -10.0f, WinScale.hY() + 2.0f, 0.0f });
	
	// Right
	R_ClickIcon->SetPosition({ 616.0f, WinScale.hY() - 24.0f, 0.0f });
	L_ClickIcon->SetPosition({ 553.0f, WinScale.hY() - 24.0f, 0.0f });
	ItemIcon->SetPosition({ 597.0f, WinScale.hY() - 2.0f, 0.0f });
	KatanaIcon->SetPosition({ 533.0f, WinScale.hY() - 2.0f, 0.0f });
	Weapon->SetPosition({ 565.0f, WinScale.hY() - 1.0f, 0.0f });

	Bar->SetPosition({ 0.0f, WinScale.hY(), 0.0f });
}

void AUp_HUD::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AUp_HUD::StateInit()
{
	// State Create
	State.CreateState(HudState::wait);
	State.CreateState(HudState::play);
	State.CreateState(HudState::outro);
	
	// State Start
	State.SetStartFunction(HudState::wait, [=] {});
	State.SetStartFunction(HudState::play, [=] {});
	State.SetStartFunction(HudState::outro, [=]	{ Off(); });
	
	// State Update
	State.SetUpdateFunction(HudState::wait, [=](float _DeltaTime) {});
	State.SetUpdateFunction(HudState::play, [=](float _DeltaTime)
		{
			APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
			float AddScaleX = (188.0f * _DeltaTime) / PlayLevel->GetTotalPlayTime();
			if (188.0f < Timer_Bar_Black->GetLocalScale().X)
			{
				AddScaleX = 0.0f;
			}

			Timer_Bar_Black->AddScale({ AddScaleX, 0.0f, 0.0f });
			Timer_Bar_Black->AddPosition({ AddScaleX * (-0.5f), 0.0f, 0.0f });
		}
	);

	State.SetUpdateFunction(HudState::outro, [=](float _DeltaTime) {});
}

void AUp_HUD::BatteryPartUpdate(float _AbilityTime)
{
	int PartSize = static_cast<int>(Battery_Part.size());
	float MaxAbilityTime = Const::player_ability_time;
	float CurAbilityTime = _AbilityTime;
	
	int OnPartNum = static_cast<int>(CurAbilityTime / (MaxAbilityTime / PartSize));
	for (int i = 0; i < OnPartNum; i++)
	{
		Battery_Part[i]->SetSprite(ImgRes::ui_up_hud_battery_part1);
	}
	
	for (int i = OnPartNum; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetSprite(ImgRes::ui_up_hud_battery_part2);
	}
}

void AUp_HUD::On()
{
	Bar->SetActive(true);

	Timer->SetActive(true);
	Timer_Bar->SetActive(true);
	Timer_Bar_Black->SetActive(true);

	Battery->SetActive(true);
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetActive(true);
	}
	Shift->SetActive(true);

	Weapon->SetActive(true);
	KatanaIcon->SetActive(true);
	ItemIcon->SetActive(true);
	L_ClickIcon->SetActive(true);
	R_ClickIcon->SetActive(true);
}

void AUp_HUD::Off()
{
	Bar->SetActive(false);

	Timer->SetActive(false);
	Timer_Bar->SetActive(false);
	Timer_Bar_Black->SetActive(false);

	Battery->SetActive(false);
	for (size_t i = 0; i < Battery_Part.size(); i++)
	{
		Battery_Part[i]->SetActive(false);
	}
	Shift->SetActive(false);

	Weapon->SetActive(false);
	KatanaIcon->SetActive(false);
	ItemIcon->SetActive(false);
	L_ClickIcon->SetActive(false);
	R_ClickIcon->SetActive(false);
}

void AUp_HUD::Reset()
{
	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	WinScale.Y -= 47.0f;
	Timer_Bar_Black->SetPosition({ 100.0f, WinScale.hY() + 5.0f, 1.0f });
	Timer_Bar_Black->SetScale({ 0.0f, 22.0f, 1.0f });
}