#include "PreCompile.h"
#include "OutroMsg.h"

#include "FadeImage.h"
#include "PlayLevelBase.h"

AOutroMsg::AOutroMsg()
{
}

AOutroMsg::~AOutroMsg()
{
}

void AOutroMsg::BeginPlay()
{
	Super::BeginPlay();

	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	Body = CreateWidget<UFadeImage>(GetWorld(), "OutroMsg");
	Body->SetSprite(ImgRes::ui_outro_msg);
	Body->SetScale({ WinScale.X, WinScale.Y, 1.0f });
	Body->SetPosition({ 0.0f, 0.0f, 0.0f });
	Body->AddToViewPort(EWidgetOrder::Top);

	StateInit();
	State.ChangeState(OutroMsgState::fade_in);
}

void AOutroMsg::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AOutroMsg::StateInit()
{
	// State Create
	State.CreateState(OutroMsgState::fade_in);
	State.CreateState(OutroMsgState::fade_out);
	State.CreateState(OutroMsgState::wait);

	// State Start
	State.SetStartFunction(OutroMsgState::fade_in, [=] { Body->SetFadeIn(); });
	State.SetStartFunction(OutroMsgState::fade_out, [=] { Body->SetFadeOut(); });
	State.SetStartFunction(OutroMsgState::wait, [=]
		{ 
			DelayCallBack(1.0f, [=]
				{
					APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
					PlayLevel->StateChange(PlayLevelState::replay);
					State.ChangeState(OutroMsgState::fade_out);
				}
			);
		}
	);
	
	// State Update
	State.SetUpdateFunction(OutroMsgState::wait, [=](float _DeltaTime) {});
	State.SetUpdateFunction(OutroMsgState::fade_in, [=](float _DeltaTime) 
		{
			Body->FadeUpdate(_DeltaTime);

			if (false == Body->IsFade())
			{
				State.ChangeState(OutroMsgState::wait);
			}
		}
	);

	State.SetUpdateFunction(OutroMsgState::fade_out, [=](float _DeltaTime) 
		{
			Body->FadeUpdate(_DeltaTime);

			if (false == Body->IsFade())
			{
				Body->SetActive(false);
				Destroy();
			}
		}
	);
}
