#include "PreCompile.h"
#include "FactoryIntroUI.h"

#include "KZImage.h"

AFactoryIntroUI::AFactoryIntroUI()
{
}

AFactoryIntroUI::~AFactoryIntroUI()
{
}

void AFactoryIntroUI::BeginPlay()
{
	Super::BeginPlay();

	ImageInit();
	StateInit();

	Off();
}

void AFactoryIntroUI::ImageInit()
{
	// Song
	SongBackGround = CreateWidget<UKZImage>(GetWorld(), "SongBackGround");
	SongBackGround->SetSprite(ImgRes::ui_songtitle_background);
	SongBackGround->AddToViewPort(EWidgetOrder::Bottom);
	SongBackGround->SetScale({ 0.0f, 95.0f, 0.0f });
	SongBackGround->SetSortType(ESortType::Left);

	PlayingSong0 = CreateWidget<UKZImage>(GetWorld(), "PlayingSong_Text0");
	PlayingSong0->SetSprite(ImgRes::ui_playingsong_0);
	PlayingSong0->AddToViewPort(EWidgetOrder::Mid);
	PlayingSong0->SetSortType(ESortType::Left);
	PlayingSong0->SetAutoSize(1.0f, true);

	PlayingSong1 = CreateWidget<UKZImage>(GetWorld(), "PlayingSong_Text1");
	PlayingSong1->SetSprite(ImgRes::ui_playingsong_1);
	PlayingSong1->AddToViewPort(EWidgetOrder::Top);
	PlayingSong1->SetSortType(ESortType::Left);
	PlayingSong1->SetAutoSize(1.0f, true);

	PlayingSongUnderLine = CreateWidget<UKZImage>(GetWorld(), "PlayingSong_UnderLine");
	PlayingSongUnderLine->SetSprite(ImgRes::ui_playingsong_underline);
	PlayingSongUnderLine->AddToViewPort(EWidgetOrder::Top);
	PlayingSongUnderLine->SetScale({ 0.0f, 95.0f, 0.0f });
	PlayingSongUnderLine->SetSortType(ESortType::Left);

	PlayingSongTitle = CreateWidget<UKZImage>(GetWorld(), "PlayingSong_Title");
	PlayingSongTitle->SetSprite(ImgRes::ui_playingsong_title);
	PlayingSongTitle->AddToViewPort(EWidgetOrder::Top);
	PlayingSongTitle->SetSortType(ESortType::Left);
	PlayingSongTitle->SetAutoSize(1.0f, true);

	// Stage Name
	StageNameBackGround = CreateWidget<UKZImage>(GetWorld(), "StageNameBackGround");
	StageNameBackGround->SetSprite(ImgRes::black_point);
	StageNameBackGround->AddToViewPort(EWidgetOrder::Bottom);
	StageNameBackGround->SetScale({ 1280.0f, 100.0f, 0.0f });
	StageNameBackGround->SetPosition(StageNameUIPos);

	StageName0 = CreateWidget<UKZImage>(GetWorld(), "StageName0");
	StageName0->SetSprite(ImgRes::ui_stagename0);
	StageName0->AddToViewPort(EWidgetOrder::Mid);
	StageName0->SetPosition(StageNameUIPos);
	StageName0->SetAutoSize(1.0f, true);

	StageName1 = CreateWidget<UKZImage>(GetWorld(), "StageName1");
	StageName1->SetSprite(ImgRes::ui_stagename1);
	StageName1->AddToViewPort(EWidgetOrder::Top);
	StageName1->SetPosition(StageNameUIPos);
	StageName1->SetAutoSize(1.0f, true);

	// Start Msg
	StartMsg = CreateWidget<UImage>(GetWorld(), "StartMsg");
	StartMsg->SetSprite(ImgRes::ui_startmsg_0);
	StartMsg->AddToViewPort(EWidgetOrder::Top);
	StartMsg->SetPosition({ -20.0f, StartMsgPosY, 0.0f });
	StartMsg->SetAutoSize(1.0f, true);

	StartMouse = CreateWidget<UImage>(GetWorld(), "StartMouse");
	StartMouse->AddToViewPort(EWidgetOrder::Top);
	StartMouse->SetPosition({ 125.0f, StartMsgPosY, 0.0f });
	StartMouse->SetAutoSize(2.0f, true);

	StartMouse->CreateAnimation(Anim::ui_start_leftclick, ImgRes::ui_start_leftclick, 0.5f, true);
	StartMouse->SetFrameCallback(Anim::ui_start_leftclick, 1, [=] {	StartMsg->SetActive(false); });
	StartMouse->SetFrameCallback(Anim::ui_start_leftclick, 2, [=] { StartMsg->SetActive(true); });
}

void AFactoryIntroUI::StateInit()
{
	// State Create
	State.CreateState(FactoryIntroUIState::intro);

	// State Start
	State.SetStartFunction(FactoryIntroUIState::intro, [=]
		{
			Order = EFactoryIntroOrder::SongBackGround;
			SongBackGround->SetActive(true);
			TimeCount = 0.0f;
			SetActive(true);
		}
	);

	// State Update
	State.SetUpdateFunction(FactoryIntroUIState::intro, [=](float _DeltaTime) 
		{
			switch (Order)
			{
			case EFactoryIntroOrder::SongBackGround:
				SongBackGroundAnim(_DeltaTime);
				break;
			case EFactoryIntroOrder::PlayingSongText:
				PlayingSongTextAnim(_DeltaTime);
				break;
			case EFactoryIntroOrder::PlayingSongTitle:
				PlayingSongTitleAnim(_DeltaTime);
				break;
			case EFactoryIntroOrder::StageName:
				StageNameAnim(_DeltaTime);
				break;
			case EFactoryIntroOrder::StartWaiting:
				StartWaitingAnim(_DeltaTime);
				break;
			default:
				break;
			}
			
		}
	);

}

void AFactoryIntroUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AFactoryIntroUI::SongBackGroundAnim(float _DeltaTime)
{
	TimeCount += _DeltaTime;
	float TargetTime = 1.0f;
	float Idx = 4.0f;
	float NextScaleX = -365.0f / powf(TargetTime, Idx) * powf(TimeCount - TargetTime, Idx) + 365.0f;
	
	SongBackGround->SetScale({ NextScaleX, 95.0f, 0.0f });
	SongBackGround->SetPosition(SongUIPos);

	if (TargetTime < TimeCount)
	{
		SongBackGround->SetScale({ 365.0f, 95.0f, 0.0f });
		SongBackGround->SetPosition(SongUIPos);

		PlayingSong0->SetFadeIn();
		PlayingSong0->SetFadeTimeWeight(2.0f);
		PlayingSong0->SetPosition(SongUIPos);
		PlayingSong0->SetActive(true);

		PlayingSong1->SetFadeIn();
		PlayingSong1->SetFadeTimeWeight(2.0f);
		PlayingSong1->SetPosition(SongUIPos);
		PlayingSong1->SetActive(true);

		PlayingSongUnderLine->SetActive(true);
		
		PlayingSongTitle->SetActive(true);
		PlayingSongTitle->SetPosition(SongUIPos);

		TimeCount = 0.0f;
		Order = EFactoryIntroOrder::PlayingSongTitle;;
	}
}

void AFactoryIntroUI::PlayingSongTextAnim(float _DeltaTime)
{
}

void AFactoryIntroUI::PlayingSongTitleAnim(float _DeltaTime)
{
	TimeCount += _DeltaTime;
	float TargetTime = 1.0f;
	float Idx = 4.0f;
	float NextScaleX = -365.0f / powf(TargetTime, Idx) * powf(TimeCount - TargetTime, Idx) + 365.0f;

	PlayingSongUnderLine->SetScale({ NextScaleX, 95.0f, 0.0f });
	PlayingSongUnderLine->SetPosition(SongUIPos);

	if (TargetTime < TimeCount)
	{
		PlayingSongUnderLine->SetScale({ 365.0f, 95.0f, 0.0f });
		PlayingSongUnderLine->SetPosition(SongUIPos);

		StageNameBackGround->SetFadeIn(0.0f, 0.5f);
		StageNameBackGround->SetActive(true);

		StageName0->SetFadeIn();
		StageName0->SetFadeTimeWeight(5.0f);
		StageName0->SetActive(true);

		StageName1->SetFadeIn();
		StageName1->SetFadeTimeWeight(5.0f);
		StageName1->SetActive(true);

		Order = EFactoryIntroOrder::StageName;
	}
}

void AFactoryIntroUI::StageNameAnim(float _DeltaTime)
{
	if (false == StageNameBackGround->IsFade())
	{
		StartMsg->SetActive(true);

		StartMouse->ChangeAnimation(Anim::ui_start_leftclick);
		StartMouse->SetActive(true);

		Order = EFactoryIntroOrder::StartWaiting;
	}
}

void AFactoryIntroUI::StartWaitingAnim(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_LBUTTON))
	{

	}
}

void AFactoryIntroUI::On()
{ 
	SongBackGround->SetActive(true);
	PlayingSong0->SetActive(true);
	PlayingSong1->SetActive(true);
	PlayingSongUnderLine->SetActive(true);
	PlayingSongTitle->SetActive(true);
	StageNameBackGround->SetActive(true);
	StageName0->SetActive(true);
	StageName1->SetActive(true);
	StartMsg->SetActive(true);
	StartMouse->SetActive(true);

	SetActive(true);
}

void AFactoryIntroUI::Off()
{
	SongBackGround->SetActive(false);
	PlayingSong0->SetActive(false);
	PlayingSong1->SetActive(false);
	PlayingSongUnderLine->SetActive(false);
	PlayingSongTitle->SetActive(false);
	StageNameBackGround->SetActive(false);
	StageName0->SetActive(false);
	StageName1->SetActive(false);
	StartMsg->SetActive(false);
	StartMouse->SetActive(false);
	
	SetActive(false);
}
