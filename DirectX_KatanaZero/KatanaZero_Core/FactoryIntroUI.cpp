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
	PlayingSong0->SetAutoSize(1.0f, true);
	PlayingSong0->SetSortType(ESortType::Left);
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
			case EFactoryIntroOrder::SongText:
				SongTextAnim(_DeltaTime);
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
		PlayingSong0->SetActive(true);
		TimeCount = 0.0f;
		Order = EFactoryIntroOrder::SongText;;
	}
}

void AFactoryIntroUI::SongTextAnim(float _DeltaTime)
{
	PlayingSong0->SetPosition(SongUIPos);
	
}

void AFactoryIntroUI::On()
{ 
	SongBackGround->SetActive(true);
	PlayingSong0->SetActive(true);
	SetActive(true);
}

void AFactoryIntroUI::Off()
{
	SongBackGround->SetActive(false);
	PlayingSong0->SetActive(false);
	SetActive(false);
}
