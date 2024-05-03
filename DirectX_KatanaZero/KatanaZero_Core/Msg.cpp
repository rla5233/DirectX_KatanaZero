#include "PreCompile.h"
#include "Msg.h"

AMsg::AMsg()
{
}

AMsg::~AMsg()
{
}

void AMsg::BeginPlay()
{
	Super::BeginPlay();

	Body = CreateWidget<UImage>(GetWorld(), "Msg");
	Body->AddToViewPort(EWidgetOrder::Top);
	Body->SetAutoSize(1.0f, true);
}

void AMsg::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMsg::On()
{
	Body->SetActive(true);
	SetActive(true);
}

void AMsg::Off()
{
	Body->SetActive(false);
	SetActive(false);
}
