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
	RightBottomText = CreateWidget<UImage>(GetWorld(), "RightBottom_Text");
	LeftTopText = CreateWidget<UImage>(GetWorld(), "LeftTop_Text");

	Mouse->CreateAnimation(Anim::ui_replay_right_click, ImgRes::ui_replay_right_click, 0.5f, true);
	Mouse->ChangeAnimation(Anim::ui_replay_right_click);
	RightBottomText->SetSprite(ImgRes::ui_replay_RB_text);

	Mouse->SetOrder(ERenderOrder::UI);
	RightBottomText->AddToViewPort(EWidgetOrder::Top);
	LeftTopText->AddToViewPort(EWidgetOrder::Top);

	Mouse->SetAutoSize(2.0f, true);
	RightBottomText->SetAutoSize(1.0f, true);
	LeftTopText->SetAutoSize(1.0f, true);

	RightBottomText->SetPosition({ 500.0f, -340.0f, 0.0f });
}

void AReplayUI::StateInit()
{
	// State Create
	State.CreateState("Play");
	State.CreateState("Stop");
	State.CreateState("Rewind");
	State.CreateState("FastPlay");


	// State Start
	State.SetStartFunction("Play", [=] 
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_play);
			LeftTopText->SetPosition({ -400.0f, 270.0f, 0.0f });
		}
	);

	State.SetStartFunction("Stop", [=] 
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_stop);
			LeftTopText->SetPosition({ -354.0f, 271.0f, 0.0f });
		}
	);

	State.SetStartFunction("Rewind", [=] 
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_rewind);
			LeftTopText->SetPosition({ -370.0f, 271.0f, 0.0f });
		}
	);

	State.SetStartFunction("FastPlay", [=]
		{
			//RightTopText->SetSprite(ImgRes::ui_replay_RT_rewind);
			//RightTopText->SetPosition({ -354.0f, 271.0f, 0.0f });
		}
	);


	// State Update
	State.SetUpdateFunction("Play", [=](float _DeltaTime) 
		{
			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE))
			{
				State.ChangeState("Stop");
				return;
			}

			if (true == IsDown('A') || true == IsDown(VK_LEFT))
			{
				State.ChangeState("Rewind");
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{
				return;
			}
		}
	);

	State.SetUpdateFunction("Stop", [=](float _DeltaTime) 
		{
			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE))
			{
				State.ChangeState("Play");
				return;
			}

			if (true == IsDown('A') || true == IsDown(VK_LEFT))
			{
				State.ChangeState("Rewind");
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{
				return;
			}
		}
	);

	State.SetUpdateFunction("Rewind", [=](float _DeltaTime) 
		{	
			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE))
			{
				State.ChangeState("Stop");
				return;
			}

			if (true == IsDown('A')|| true == IsDown(VK_LEFT))
			{
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{
				State.ChangeState("Play");
				return;
			}
		}
	);

	State.SetUpdateFunction("FastPlay", [=](float _DeltaTime)
		{
			MousePosUpdate();

			// State Change Check
			if (true == IsDown('A') || true == IsDown(VK_LEFT))
			{
				State.ChangeState("Play");
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{
				return;
			}
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
