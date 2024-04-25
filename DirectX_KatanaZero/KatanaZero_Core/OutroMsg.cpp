#include "PreCompile.h"
#include "OutroMsg.h"

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
	Body = CreateWidget<UImage>(GetWorld(), "OutroMsg");
	Body->SetSprite(ImgRes::ui_outro_msg);
	Body->SetScale({ WinScale.X, WinScale.Y, 1.0f });
	Body->SetPosition({ 0.0f, 0.0f, 0.0f });
	Body->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	Body->AddToViewPort(EWidgetOrder::Top);

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

	// State Start
	State.SetStartFunction(OutroMsgState::fade_in, [=] {});
	State.SetStartFunction(OutroMsgState::fade_out, [=] {});

	
	// State Update
	State.SetUpdateFunction(OutroMsgState::fade_in, [=](float _DeltaTime) {});
	State.SetUpdateFunction(OutroMsgState::fade_out, [=](float _DeltaTime) {});


	// State End


}
