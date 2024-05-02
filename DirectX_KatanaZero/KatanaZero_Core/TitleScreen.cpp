#include "PreCompile.h"
#include "TitleScreen.h"

#include "TitleGameMode.h"

ATitleScreen::ATitleScreen()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	BackGround	= CreateDefaultSubObject<USpriteRenderer>("BackGround");
	Fence		= CreateDefaultSubObject<USpriteRenderer>("Fence");
	Plants		= CreateDefaultSubObject<USpriteRenderer>("Plants");
	Grass		= CreateDefaultSubObject<USpriteRenderer>("Grass");
	Black		= CreateDefaultSubObject<USpriteRenderer>("Black");

	Neon_ZER	= CreateDefaultSubObject<USpriteRenderer>("Neon_ZER");
	Neon_O		= CreateDefaultSubObject<USpriteRenderer>("Neon_O");
	Neon_Katana = CreateDefaultSubObject<USpriteRenderer>("Neon_Katana");

	BackGround->SetupAttachment(Root);
	Fence->SetupAttachment(Root);
	Plants->SetupAttachment(Root);
	Grass->SetupAttachment(Root);
	Black->SetupAttachment(Root);

	Neon_ZER->SetupAttachment(Root);
	Neon_O->SetupAttachment(Root);
	Neon_Katana->SetupAttachment(Root);

	SetRoot(Root);
}

ATitleScreen::~ATitleScreen()
{
} 

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	ULerpObject::SetActor(this);

	SettingSprite();
	SettingRenderOrder();
	SettingTransform();
	StateInit();

	State.ChangeState(TitleScreenState::begin);
}

void ATitleScreen::SettingSprite()
{
	BackGround->SetSprite(ImgRes::title_background);
	Fence->SetSprite(ImgRes::title_fence);
	Plants->SetSprite(ImgRes::title_plant);
	Grass->SetSprite(ImgRes::title_grass);
	Black->SetSprite(ImgRes::title_black);

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
	Black->SetOrder(ETitleRenderOrder::UpText);

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
	
	Black->SetScale({ 1280.0f, 700.0f, 0.0f });

	Neon_ZER->SetAutoSize(1.25f, true);
	Neon_O->SetAutoSize(1.25f, true);
	Neon_Katana->SetAutoSize(1.5f, true);

	Plants->SetPosition({ 0.0f, -465.0f, 0.0f });
	Grass->SetPosition({ 0.0f, -690.0f, 0.0f });
	Black->SetPosition({ 0.0f, -1150.0f, 0.0f });
	Neon_ZER->SetPosition({ 0.0f, -300.0f, 0.0f });
	Neon_O->SetPosition({ 0.0f, -300.0f, 0.0f });
	Neon_Katana->SetPosition({ 0.0f, -240.0f, 0.0f });
}

void ATitleScreen::StateInit()
{
	// State Create
	State.CreateState(TitleScreenState::none);
	State.CreateState(TitleScreenState::begin);
	State.CreateState(TitleScreenState::exit);
	State.CreateState(TitleScreenState::newgame);

	// State Start
	State.SetStartFunction(TitleScreenState::none, [=] {});
	State.SetStartFunction(TitleScreenState::begin, [=]
		{
			Plants->CreateAnimation(Anim::plants, ImgRes::title_plant, 0.1f, true);
			Plants->ChangeAnimation(Anim::plants);
		}
	);

	State.SetStartFunction(TitleScreenState::exit, [=]
		{ 
			ATitleGameMode* Title = dynamic_cast<ATitleGameMode*>(GetWorld()->GetGameMode().get());
			Title->MenuInputOff();
			SetTitleEndAim(); 
		}
	);
	
	State.SetStartFunction(TitleScreenState::newgame, [=]
		{ 
			ATitleGameMode* Title = dynamic_cast<ATitleGameMode*>(GetWorld()->GetGameMode().get());
			Title->MenuInputOff();
			SetTitleEndAim(); 
		}
	);

	// State Update
	State.SetUpdateFunction(TitleScreenState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(TitleScreenState::begin, [=](float _DeltaTime) {});
	State.SetUpdateFunction(TitleScreenState::exit, [=](float _DeltaTime)
		{
			LerpMoveUpdate(_DeltaTime, TitleOutTimeWeight);
			TitleOutTimeWeight += 0.8f * _DeltaTime;

			if (false == IsLerpMove())
			{
				GEngine->EngineWindow.Off();
			}
		}
	);

	State.SetUpdateFunction(TitleScreenState::newgame, [=](float _DeltaTime)
		{
			LerpMoveUpdate(_DeltaTime, TitleOutTimeWeight);
			TitleOutTimeWeight += 0.8f * _DeltaTime;

			if (false == IsLerpMove())
			{
				GEngine->ChangeLevel("Factory_002");
				State.ChangeState(TitleScreenState::none);
				return;
			}
		}
	);
}

void ATitleScreen::SetTitleEndAim()
{
	FVector StartPos = GetActorLocation();
	FVector TargetPos = StartPos + FVector(0.0f, 720.0f, 0.0f);
	SetLerpMovePos(StartPos, TargetPos);
	Grass->SetOrder(ETitleRenderOrder::UpText);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}