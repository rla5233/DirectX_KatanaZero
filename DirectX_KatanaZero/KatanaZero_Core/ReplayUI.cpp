#include "PreCompile.h"
#include "ReplayUI.h"

AReplayUI::AReplayUI()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Mouse = CreateDefaultSubObject<USpriteRenderer>("Mouse");
	Mouse->SetupAttachment(Root);

	SetRoot(Root);
}

AReplayUI::~AReplayUI()
{
}

void AReplayUI::BeginPlay()
{
	Super::BeginPlay();

	ImageInit();
	StateInit();

	State.ChangeState("Play");
}

void AReplayUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AReplayUI::ImageInit()
{
	//Mouse = CreateWidget<UImage>(GetWorld(), "Replay_Mouse");
	LeftBottomText = CreateWidget<UImage>(GetWorld(), "LeftBottom_Text");
	RightTopText = CreateWidget<UImage>(GetWorld(), "RightTop_Text");

	Mouse->CreateAnimation(Anim::ui_replay_right_click, ImgRes::ui_replay_right_click, 0.5f, true);
	Mouse->ChangeAnimation(Anim::ui_replay_right_click);
	LeftBottomText->SetSprite(ImgRes::ui_replay_LB_text);
	RightTopText->SetSprite(ImgRes::ui_replay_RT_play);

	Mouse->SetOrder(ERenderOrder::UI);
	LeftBottomText->AddToViewPort(EWidgetOrder::Top);
	RightTopText->AddToViewPort(EWidgetOrder::Top);

	Mouse->SetAutoSize(2.0f, true);
	LeftBottomText->SetAutoSize(1.0f, true);
	RightTopText->SetAutoSize(1.0f, true);

	LeftBottomText->SetPosition({ 500.0f, -340.0f, 0.0f });
}

void AReplayUI::StateInit()
{
	// State Create
	State.CreateState("Play");


	// State Start
	State.SetStartFunction("Play", [=] {});


	// State Update
	State.SetUpdateFunction("Play", [=](float _DeltaTime) 
		{
			MousePosUpdate();
		}
	);
}

void AReplayUI::MousePosUpdate()
{
	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	CameraPos.X += 500.0f;
	CameraPos.Y += -305.0f;
	CameraPos.Z = 0.0f;
	Mouse->SetPosition(CameraPos);
}
