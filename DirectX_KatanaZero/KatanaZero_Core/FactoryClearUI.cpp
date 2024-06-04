#include "PreCompile.h"
#include "FactoryClearUI.h"

#include "KZImage.h"

UFactoryClearUI::UFactoryClearUI()
{
}

UFactoryClearUI::~UFactoryClearUI()
{
}

void UFactoryClearUI::BeginPlay()
{
	Super::BeginPlay();
	
	ImageInit();
	StateInit();
	Off();
}

void UFactoryClearUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void UFactoryClearUI::ImageInit()
{
	ClearText0 = CreateWidget<UKZImage>(GetWorld(), "Clear_Text0");
	ClearText0->AddToViewPort(EWidgetOrder::Mid);
	ClearText0->SetSprite(ImgRes::ui_stage_clear0);
	ClearText0->SetAutoSize(1.0f, true);
	
	ClearText1 = CreateWidget<UKZImage>(GetWorld(), "Clear_Text1");
	ClearText1->AddToViewPort(EWidgetOrder::Top);
	ClearText1->SetSprite(ImgRes::ui_stage_clear1);
	ClearText1->SetAutoSize(1.0f, true);

	ClearBackGround = CreateWidget<UKZImage>(GetWorld(), "Clear_BackGround");
	ClearBackGround->AddToViewPort(EWidgetOrder::Bottom);
	ClearBackGround->SetScale({ 1280.0f, 60.0f, 0.0f });
	ClearBackGround->SetSprite(ImgRes::black_point);
	ClearBackGround->SetPosition(ClearUIPos);

}

void UFactoryClearUI::StateInit()
{
	// State Create
	State.CreateState(FactoryClearUIState::clear);
	
	// State Start
	State.SetStartFunction(FactoryClearUIState::clear, [=] 
		{
			ClearText0->SetFadeIn();
			ClearText0->SetFadeTimeWeight(2.0f);
			ClearText0->SetLerpMovePos(ClearUIPos - FVector(500.0f, 0.0f, 0.0f), ClearUIPos);
			ClearText0->SetShakeRefPosition(ClearUIPos - FVector(500.0f, 0.0f, 0.0f));
			ClearText0->SetShakeRange({ -1.0f, 1.0f, -1.0f, 1.0f });
			ClearText0->SetShakeActive(true);

			ClearText1->SetFadeIn();
			ClearText1->SetFadeTimeWeight(2.0f);
			ClearText1->SetLerpMovePos(ClearUIPos + FVector(500.0f, 0.0f, 0.0f), ClearUIPos);
			ClearText1->SetShakeRefPosition(ClearUIPos + FVector(500.0f, 0.0f, 0.0f));
			ClearText1->SetShakeRange({ -1.0f, 1.0f, -1.0f, 1.0f });
			ClearText1->SetShakeActive(true);

			ClearBackGround->SetFadeIn(0.0f, 0.5f);
			
			ClearMoveTimeWeight = 3.0f;
			Order = EFactoryClearOrder::FactoryClearStart;
			UEngineSound::SoundPlay(SoundRes::stage_start);
			USoundManager::GetInst().GetFactoryBGM().Off();
			USoundManager::GetInst().ResetFactoryBGM();
			On();
		}
	);

	// State Update
	State.SetUpdateFunction(FactoryClearUIState::clear, [=](float _DeltaTime) 
		{
			switch (Order)
			{
			case EFactoryClearOrder::FactoryClearStart:
				FactoryClearStart(_DeltaTime);
				break;
			case EFactoryClearOrder::FactoryClearEnd:
				FactoryClearEnd(_DeltaTime);
				break;
			default:
				break;
			}
		}
	);

}

void UFactoryClearUI::FactoryClearStart(float _DeltaTime)
{
	ClearMoveTimeWeight -= 4.52f * _DeltaTime;

	ClearText0->SetLerpTimeWeight(ClearMoveTimeWeight);
	ClearText1->SetLerpTimeWeight(ClearMoveTimeWeight);

	if (false == ClearText0->IsLerpMove() && false == ClearText1->IsLerpMove())
	{
		ClearText0->SetShakeRefPosition(ClearUIPos);
		ClearText1->SetShakeRefPosition(ClearUIPos);

		Order = EFactoryClearOrder::None;

		DelayCallBack(3.0f, [=]
			{
				ClearMoveTimeWeight = 0.1f;

				ClearText0->SetFadeOut();
				ClearText0->SetFadeTimeWeight(1.0f);
				ClearText0->SetLerpMovePos(ClearUIPos, ClearUIPos - FVector(500.0f, 0.0f, 0.0f));
				ClearText0->SetLerpTimeWeight(ClearMoveTimeWeight);
				ClearText0->SetShakeRefPosition(ClearUIPos);
				ClearText0->SetShakeRange({ -1.0f, 1.0f, -1.0f, 1.0f });
				ClearText0->SetShakeActive(true);

				ClearText1->SetFadeOut();
				ClearText1->SetFadeTimeWeight(1.0f);
				ClearText1->SetLerpMovePos(ClearUIPos, ClearUIPos + FVector(500.0f, 0.0f, 0.0f));
				ClearText1->SetLerpTimeWeight(ClearMoveTimeWeight);
				ClearText1->SetShakeRefPosition(ClearUIPos);
				ClearText1->SetShakeRange({ -1.0f, 1.0f, -1.0f, 1.0f });
				ClearText1->SetShakeActive(true);

				ClearBackGround->SetFadeOut(0.5f, 0.0f);

				Order = EFactoryClearOrder::FactoryClearEnd;
			}
		);
	}
}

void UFactoryClearUI::FactoryClearEnd(float _DeltaTime)
{
	ClearMoveTimeWeight += 4.52f * _DeltaTime;

	ClearText0->SetLerpTimeWeight(ClearMoveTimeWeight);
	ClearText1->SetLerpTimeWeight(ClearMoveTimeWeight);

	if (false == ClearText0->IsLerpMove() && false == ClearText1->IsLerpMove())
	{
		Order = EFactoryClearOrder::None;
		Off();
	}
}

void UFactoryClearUI::On()
{
	ClearText0->SetActive(true);
	ClearText1->SetActive(true);
	ClearBackGround->SetActive(true);

	SetActive(true);
}

void UFactoryClearUI::Off()
{
	ClearText0->SetActive(false);
	ClearText1->SetActive(false);
	ClearBackGround->SetActive(false);

	SetActive(false);
}