#include "PreCompile.h"
#include "HeadHunter_Phase2.h"

AHeadHunter_Phase2::AHeadHunter_Phase2()
{
}

AHeadHunter_Phase2::~AHeadHunter_Phase2()
{
}

void AHeadHunter_Phase2::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f,0.0f,-100.0f });
}

void AHeadHunter_Phase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
