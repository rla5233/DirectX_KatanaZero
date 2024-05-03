#include "PreCompile.h"
#include "FailedMsg.h"

AFailedMsg::AFailedMsg()
{
}

AFailedMsg::~AFailedMsg()
{
}

void AFailedMsg::BeginPlay()
{
	Super::BeginPlay();

	ImageInit();
	StateInit();
	Off();
}

void AFailedMsg::ImageInit()
{
	Body = CreateWidget<UImage>(GetWorld(), "FailedMsg");
	Body->AddToViewPort(EWidgetOrder::Top);
	Body->SetAutoSize(1.0f, true);

	BackGround = CreateWidget<UImage>(GetWorld(), "FailedMsg");
	BackGround->AddToViewPort(EWidgetOrder::Mid);
	BackGround->SetSprite(ImgRes::black_point);
	BackGround->SetScale({ 350.0f, 200.0f, 0.0f });
	BackGround->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.3f });
}

void AFailedMsg::StateInit()
{
	// State Create
	State.CreateState(FailedMsgState::hit_end);

	// State Start
	State.SetStartFunction(FailedMsgState::hit_end, [=]
		{
			Body->SetSprite(ImgRes::ui_playerdead_msg_0);
			On();
		}
	);

	// State Update
	State.SetUpdateFunction(FailedMsgState::hit_end, [=](float _DeltaTime)
		{

		}
	);
}

void AFailedMsg::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AFailedMsg::On()
{
	BackGround->SetActive(true);
	Body->SetActive(true);
	SetActive(true);
}

void AFailedMsg::Off()
{
	BackGround->SetActive(false);
	Body->SetActive(false);
	SetActive(false);
}
