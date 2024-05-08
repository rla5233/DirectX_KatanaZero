#include "PreCompile.h"
#include "HeadHunterPhase2.h"

AHeadHunterPhase2::AHeadHunterPhase2()
{
}

AHeadHunterPhase2::~AHeadHunterPhase2()
{
}

void AHeadHunterPhase2::BeginPlay()
{
	Super::BeginPlay();

	Hp = 10;
}

void AHeadHunterPhase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}