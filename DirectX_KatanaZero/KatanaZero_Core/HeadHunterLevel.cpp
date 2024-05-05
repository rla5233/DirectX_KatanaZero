#include "PreCompile.h"
#include "HeadHunterLevel.h"

AHeadHunterLevel::AHeadHunterLevel()
{
}

AHeadHunterLevel::~AHeadHunterLevel()
{
}

void AHeadHunterLevel::BeginPlay()
{
	Super::BeginPlay();
}

void AHeadHunterLevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void AHeadHunterLevel::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

bool AHeadHunterLevel::IsStageClear()
{
	return false;
}

void AHeadHunterLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}