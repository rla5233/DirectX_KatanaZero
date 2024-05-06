#include "PreCompile.h"
#include "HeadHunterLevel.h"

#include "HeadHunter.h"

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

void AHeadHunterLevel::PlayStart()
{
	Super::PlayStart();

	HeadHunter->SetRecordingActive(true);
}

void AHeadHunterLevel::PlayerDeadStart()
{
	Super::PlayerDeadStart();

	HeadHunter->SetRecordingActive(false);
}

void AHeadHunterLevel::RestartStart()
{
	Super::RestartStart();

	HeadHunter->SubStateChange(HeadHunterSubState::restart);
}
