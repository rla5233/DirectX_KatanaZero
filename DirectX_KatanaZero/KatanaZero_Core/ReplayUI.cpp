#include "PreCompile.h"
#include "ReplayUI.h"

#include "PlayLevelBase.h"

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

void AReplayUI::On()
{
	SetActive(true);
	Mouse->SetActive(true);
	LeftTopText->SetActive(true);
	RightBottomText->SetActive(true);
}

void AReplayUI::Off()
{
	SetActive(false);
	Mouse->SetActive(false);
	LeftTopText->SetActive(false);
	Speed->SetActive(false);
	RightBottomText->SetActive(false);
}

void AReplayUI::BeginPlay()
{
	Super::BeginPlay();

	ImageInit();
	StateInit();
	InputOn();

	PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	State.ChangeState(ReplayUIState::play);
}

void AReplayUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AReplayUI::ImageInit()
{
	RightBottomText = CreateWidget<UImage>(GetWorld(), "RightBottom_Text");
	LeftTopText = CreateWidget<UImage>(GetWorld(), "LeftTop_Text");
	Speed = CreateWidget<UImage>(GetWorld(), "Speed");
	Speed->SetActive(false);

	Mouse->CreateAnimation(Anim::ui_replay_right_click, ImgRes::ui_replay_right_click, 0.5f, true);
	Mouse->ChangeAnimation(Anim::ui_replay_right_click);
	RightBottomText->SetSprite(ImgRes::ui_replay_RB_text);

	Mouse->SetOrder(ERenderOrder::UI);
	RightBottomText->AddToViewPort(EWidgetOrder::Mid);
	LeftTopText->AddToViewPort(EWidgetOrder::Mid);
	Speed->AddToViewPort(EWidgetOrder::Mid);

	Mouse->SetAutoSize(2.0f, true);
	RightBottomText->SetAutoSize(1.0f, true);
	LeftTopText->SetAutoSize(1.0f, true);
	Speed->SetAutoSize(1.0f, true);

	RightBottomText->SetPosition({ 500.0f, -340.0f, 0.0f });
}

void AReplayUI::StateInit()
{
	// State Create
	State.CreateState(ReplayUIState::play);
	State.CreateState(ReplayUIState::stop);
	State.CreateState(ReplayUIState::rewind);
	State.CreateState(ReplayUIState::fastplay);


	// State Start
	State.SetStartFunction(ReplayUIState::play, [=]
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_play);
			LeftTopText->SetPosition({ -400.0f, 270.0f, 0.0f });
			PlayLevel->SetReplay();
			Speed->SetActive(false);
		}
	);

	State.SetStartFunction(ReplayUIState::stop, [=]
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_stop);
			LeftTopText->SetPosition({ -354.0f, 271.0f, 0.0f });
			PlayLevel->SetReplayStop();
			Speed->SetActive(false);
		}
	);

	State.SetStartFunction(ReplayUIState::rewind, [=]
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_rewind);
			LeftTopText->SetPosition({ -380.0f, 271.0f, 0.0f });
			PlayLevel->SetRewind();

			SpeedIdx = 0;
		}
	);

	State.SetStartFunction(ReplayUIState::fastplay, [=]
		{
			LeftTopText->SetSprite(ImgRes::ui_replay_LT_fast);
			LeftTopText->SetPosition({ -347.0f, 271.0f, 0.0f });
			PlayLevel->SetReplay();
			PlayLevel->IncreaseReplaySpeed();

			SpeedIdx = 1;
			Speed->SetActive(true);
			Speed->SetSprite(ImgRes::ui_replay_x2);
			Speed->SetPosition({ -220.0f, 271.0f, 0.0f });
		}
	);

	// State Update
	State.SetUpdateFunction(ReplayUIState::play, [=](float _DeltaTime)
		{

			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE) || true == PlayLevel->IsReplayEnd())
			{
				State.ChangeState(ReplayUIState::stop);
				return;
			}

			if (true == IsDown('A') || true == IsDown(VK_LEFT))
			{
				State.ChangeState(ReplayUIState::rewind);
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{	
				State.ChangeState(ReplayUIState::fastplay);
				return;
			}
		}
	);

	State.SetUpdateFunction(ReplayUIState::stop, [=](float _DeltaTime)
		{
			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE) && false == PlayLevel->IsReplayEnd())
			{
				State.ChangeState(ReplayUIState::play);
				return;
			}

			if ((true == IsDown('A') || true == IsDown(VK_LEFT))
			&& (false == PlayLevel->IsRewindEnd()))
			{
				State.ChangeState(ReplayUIState::rewind);
				return;
			}

			if ((true == IsDown('D') || true == IsDown(VK_RIGHT))
			&& (false == PlayLevel->IsReplayEnd()))
			{
				State.ChangeState(ReplayUIState::fastplay);
				return;
			}
		}
	);

	State.SetUpdateFunction(ReplayUIState::rewind, [=](float _DeltaTime)
		{	
			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE) || true == PlayLevel->IsRewindEnd())
			{
				State.ChangeState(ReplayUIState::stop);
				return;
			}

			if (true == IsDown('A')|| true == IsDown(VK_LEFT))
			{
				SetRewindSpeedImage();
				PlayLevel->IncreaseReplaySpeed();
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{
				State.ChangeState(ReplayUIState::play);
				return;
			}
		}
	);

	State.SetUpdateFunction(ReplayUIState::fastplay, [=](float _DeltaTime)
		{
			MousePosUpdate();

			// State Change Check
			if (true == IsDown(VK_SPACE) || true == PlayLevel->IsReplayEnd())
			{
				State.ChangeState(ReplayUIState::stop);
				return;
			}

			if (true == IsDown('A') || true == IsDown(VK_LEFT))
			{
				State.ChangeState(ReplayUIState::play);
				return;
			}

			if (true == IsDown('D') || true == IsDown(VK_RIGHT))
			{
				SetFastSpeedImage();
				PlayLevel->IncreaseReplaySpeed();
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

void AReplayUI::SetFastSpeedImage()
{
	++SpeedIdx;
	if (4 < SpeedIdx)
	{
		SpeedIdx = 4;
	}

	switch (SpeedIdx)
	{
	case 1:
		Speed->SetSprite(ImgRes::ui_replay_x2);
		Speed->SetPosition({ -220.0f, 271.0f, 0.0f });
		break;
	case 2:
		Speed->SetSprite(ImgRes::ui_replay_x4);
		Speed->SetPosition({ -220.0f, 271.0f, 0.0f });
		break;
	case 3:
		Speed->SetSprite(ImgRes::ui_replay_x8);
		Speed->SetPosition({ -220.0f, 271.0f, 0.0f });
		break;
	case 4:
		Speed->SetSprite(ImgRes::ui_replay_x16);
		Speed->SetPosition({ -220.0f, 271.0f, 0.0f });
		break;
	default:
		break;
	}
}

void AReplayUI::SetRewindSpeedImage()
{
	++SpeedIdx;
	if (4 < SpeedIdx)
	{
		SpeedIdx = 4;
	}

	switch (SpeedIdx)
	{
	case 1:
		Speed->SetSprite(ImgRes::ui_replay_x2);
		Speed->SetPosition({ -280.0f, 271.0f, 0.0f });
		Speed->SetActive(true);
		break;
	case 2:
		Speed->SetSprite(ImgRes::ui_replay_x4);
		Speed->SetPosition({ -280.0f, 271.0f, 0.0f });
		Speed->SetActive(true);
		break;
	case 3:
		Speed->SetSprite(ImgRes::ui_replay_x8);
		Speed->SetPosition({ -280.0f, 271.0f, 0.0f });
		Speed->SetActive(true);
		break;
	case 4:
		Speed->SetSprite(ImgRes::ui_replay_x16);
		Speed->SetPosition({ -280.0f, 271.0f, 0.0f });
		Speed->SetActive(true);
		break;
	default:
		break;
	}
}
