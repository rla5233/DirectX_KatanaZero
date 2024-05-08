#include "PreCompile.h"
#include "HeadHunter_Phase2.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "MainCamera.h"

#include "HeadHunterPhase1.h"

AHeadHunter_Phase2::AHeadHunter_Phase2()
{
}

AHeadHunter_Phase2::~AHeadHunter_Phase2()
{
}

void AHeadHunter_Phase2::BeginPlay()
{
	Super::BeginPlay();
}

void AHeadHunter_Phase2::LevelStart(ULevel* _PrevLevel)
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


	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);


	State.ChangeState(BossLevelState::transition_off);
}

void AHeadHunter_Phase2::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AHeadHunter_Phase2::LevelReStart()
{
	Super::LevelReStart();
}

void AHeadHunter_Phase2::LevelReEnd()
{
	Super::LevelReEnd();
}

void AHeadHunter_Phase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
