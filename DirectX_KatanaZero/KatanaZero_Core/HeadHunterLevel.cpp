#include "PreCompile.h"
#include "HeadHunterLevel.h"

#include "HeadHunterBase.h"

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

	HeadHunter->Destroy();
	HeadHunter = nullptr;
}

void AHeadHunterLevel::LevelReEnd()
{
	Super::LevelReEnd();

	HeadHunter->Destroy();
	HeadHunter = nullptr;
}

bool AHeadHunterLevel::IsStageClear()
{
	return false;
}

void AHeadHunterLevel::BrightnessUp(float _DeltaTime)
{
	Super::BrightnessUp(_DeltaTime);

	if (true == BrightnessUpEnd)
	{
		return;
	}

	HeadHunter->GetBody()->SetMulColor(EnemyBrightness);
}

void AHeadHunterLevel::BrightnessDown(float _DeltaTime)
{
	Super::BrightnessDown(_DeltaTime);

	if (true == BrightnessDownEnd)
	{
		return;
	}

	HeadHunter->GetBody()->SetMulColor(EnemyBrightness);
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

	HeadHunter->StateChange(HeadHunterState::none);
	HeadHunter->SubStateChange(HeadHunterSubState::restart);
}