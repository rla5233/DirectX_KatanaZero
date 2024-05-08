#include "PreCompile.h"
#include "HeadHunterLevel_Phase2.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "MainCamera.h"

#include "HeadHunterPhase2.h"

AHeadHunterLevel_Phase2::AHeadHunterLevel_Phase2()
{
}

AHeadHunterLevel_Phase2::~AHeadHunterLevel_Phase2()
{
}

void AHeadHunterLevel_Phase2::BeginPlay()
{
	Super::BeginPlay();
}

void AHeadHunterLevel_Phase2::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 100.0f;

	ColMap->SetColMapSprite(ImgRes::headhunter_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::headhunter_background2, 2.0f, true);
	ColMap->SetBGSpritePosition({ 672.0f, 425.0f, 0.0f });

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 380.0f, 680.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);
	Player->SetIntroType(EIntroType::HeadHunter2);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase2>("HeadHunter", EUpdateOrder::Enemy);
	HeadHunter->SetActorLocation({ 978.0f, 160.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);

	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);

	State.ChangeState(BossLevelState::transition_off);

	DelayCallBack(2.5f, [=]
		{
			Player->StateChange(PlayerState::idle);
			Player->SubStateChange(PlayerSubState::none);

			DelayCallBack(0.8f, [=]
				{
					HeadHunter->SubStateChange(HeadHunterSubState::play);
				}
			);
		}
	);
}

void AHeadHunterLevel_Phase2::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AHeadHunterLevel_Phase2::LevelReStart()
{
	Super::LevelReStart();

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 380.0f, 680.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);
	Player->SetIntroType(EIntroType::HeadHunter2);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase2>("HeadHunter", EUpdateOrder::Enemy);
	HeadHunter->SetActorLocation({ 980.0f, 175.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);
}

void AHeadHunterLevel_Phase2::LevelReEnd()
{
	Super::LevelReEnd();
}

void AHeadHunterLevel_Phase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
