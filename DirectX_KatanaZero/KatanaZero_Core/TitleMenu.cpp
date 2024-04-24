#include "PreCompile.h"
#include "TitleMenu.h"

#include "TitleGameMode.h"

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

	BlackBar->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	WhiteBar->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.25f });
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
	WhiteBar->SetScale({ 500.0f, 37.0f, 1.0f });

	WhiteBar->SetPosition(WhiteBarPos);
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
	State.CreateState("Wait");

	// State Start
	State.SetStartFunction("TitleEnter", [=] 
		{
			FVector StartPos = { 0.0f, -800.0f, 0.0f };
			FVector TargetPos = { 0.0f, -520.0f, 0.0f };
			SetLerpMovePos(StartPos, TargetPos);

			InputOn();
		}
	);

	State.SetStartFunction("Wait", [=] {});

	// State Update
	State.SetUpdateFunction("TitleEnter", [=] (float _DeltaTime)
		{
			LerpMoveUpdate(_DeltaTime, EnterTitleTimeWeight);
			EnterTitleTimeWeight -= 2.0f * _DeltaTime;
			InputCheck();

			if (false == IsLerpMove())
			{
				State.ChangeState("Wait");
				return;
			}
		}
	);

	State.SetUpdateFunction("Wait", [=](float _DeltaTime) { InputCheck(); });
}

void ATitleMenu::InputCheck()
{
	if (true == IsDown('W') || true == IsDown(VK_UP))
	{
		CurMenuIdx--;
		if (0 > CurMenuIdx)
		{
			CurMenuIdx = 0;
		}
	}

	if (true == IsDown('S') || true == IsDown(VK_DOWN))
	{
		CurMenuIdx++;
		if (MenuNum <= CurMenuIdx)
		{
			CurMenuIdx = MenuNum - 1;
		}
	}

	if (true == IsDown(VK_SPACE) || true == IsDown(VK_RETURN))
	{
		ATitleGameMode* Title = dynamic_cast<ATitleGameMode*>(GetWorld()->GetGameMode().get());
		Title->InputCheck(CurMenuIdx);
	}

	WhiteBarPosUpdate();
}

void ATitleMenu::WhiteBarPosUpdate()
{
	FVector NextPos = WhiteBarPos;
	NextPos.Y -= WhiteBarInterVal * CurMenuIdx;
	WhiteBar->SetPosition(NextPos);
}
