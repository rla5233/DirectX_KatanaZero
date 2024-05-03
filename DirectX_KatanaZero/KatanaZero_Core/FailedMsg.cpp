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

	StateInit();

	Body = CreateWidget<UImage>(GetWorld(), "FailedMsg");
	Body->AddToViewPort(EWidgetOrder::Top);
	Body->SetAutoSize(1.0f, true);
}

void AFailedMsg::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFailedMsg::StateInit()
{
}

void AFailedMsg::On()
{
	Body->SetActive(true);
	SetActive(true);
}

void AFailedMsg::Off()
{
	Body->SetActive(false);
	SetActive(false);
}
