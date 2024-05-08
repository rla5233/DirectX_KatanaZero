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

FVector AHeadHunterLevel::FindExitDoor()
{
	return FVector();
}

float AHeadHunterLevel::GetRefPosX(std::string_view _Key)
{
	std::string Key = UEngineString::ToUpper(_Key);

	if (false == RefPosX.contains(Key))
	{
		MsgBoxAssert("올바르지 않은 Key 값입니다.");
	}

	return RefPosX[Key];
}

void AHeadHunterLevel::AddRefPosX(std::string_view _Key, float _PosX)
{
	std::string Key = UEngineString::ToUpper(_Key);

	if (true == RefPosX.contains(Key))
	{
		MsgBoxAssert("이미 존재하는 Key 값입니다.");
	}

	RefPosX[Key] = _PosX;
}