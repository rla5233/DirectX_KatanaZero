#include "PreCompile.h"
#include "HeadHunter_Phase1.h"

AHeadHunter_Phase1::AHeadHunter_Phase1()
{
}

AHeadHunter_Phase1::~AHeadHunter_Phase1()
{
}

void AHeadHunter_Phase1::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 0.0f, 0.0f, -100.0f });
}

void AHeadHunter_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
