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
	InputOn();

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
	State.CreateState("Stop");
	State.CreateState("Rewind");


	// State Start
	State.SetStartFunction("Play", [=] 
		{
			RightTopText->SetSprite(ImgRes::ui_replay_RT_play);
			RightTopText->SetPosition({ -400.0f, 270.0f, 0.0f });
		}
	);

	State.SetStartFunction("Stop", [=] 
		{
			RightTopText->SetSprite(ImgRes::ui_replay_RT_stop);
			RightTopText->SetPosition({ -354.0f, 271.0f, 0.0f });
		}
	);

	State.SetStartFunction("Rewind", [=] {});


	// State Update
	State.SetUpdateFunction("Play", [=](float _DeltaTime) 
		{
			InputCheck();
			MousePosUpdate();
		}
	);

	State.SetUpdateFunction("Stop", [=](float _DeltaTime) 
		{
			InputCheck();
			MousePosUpdate();
		}
	);
	State.SetUpdateFunction("Rewind", [=](float _DeltaTime) {});
}

void AReplayUI::InputCheck()
{
	if (true == IsDown(VK_SPACE))
	{
		if ("Play" == State.GetCurStateName())
		{
			State.ChangeState("Stop");
			return;
		}

		if ("Stop" == State.GetCurStateName())
		{
			State.ChangeState("Play");
			return;
		}
	}

	if (true == IsDown('A') || true == IsDown(VK_LEFT))
	{

	}
}

void AReplayUI::MousePosUpdate()
{
	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	CameraPos.X += 500.0f;
	CameraPos.Y += -305.0f;
	CameraPos.Z = 0.0f;
	Mouse->SetPosition(CameraPos);
}
