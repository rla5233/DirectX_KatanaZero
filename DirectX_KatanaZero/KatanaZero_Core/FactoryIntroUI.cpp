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
	PlayingSongUnderLine->SetSortType(ESortType::Left);
	PlayingSongUnderLine->SetAutoSize(1.0f, true);

	PlayingSongTitle = CreateWidget<UKZImage>(GetWorld(), "PlayingSong_Title");
	PlayingSongTitle->SetSprite(ImgRes::ui_playingsong_title);
	PlayingSongTitle->AddToViewPort(EWidgetOrder::Top);
	PlayingSongTitle->SetSortType(ESortType::Left);
	PlayingSongTitle->SetAutoSize(1.0f, true);
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

		Order = EFactoryIntroOrder::None;
	}
}

void AFactoryIntroUI::On()
{ 
	SongBackGround->SetActive(true);
	PlayingSong0->SetActive(true);
	PlayingSong1->SetActive(true);
	PlayingSongUnderLine->SetActive(true);
	PlayingSongTitle->SetActive(true);

	SetActive(true);
}

void AFactoryIntroUI::Off()
{
	SongBackGround->SetActive(false);
	PlayingSong0->SetActive(false);
	PlayingSong1->SetActive(false);
	PlayingSongUnderLine->SetActive(false);
	PlayingSongTitle->SetActive(false);
	
	SetActive(false);
}
