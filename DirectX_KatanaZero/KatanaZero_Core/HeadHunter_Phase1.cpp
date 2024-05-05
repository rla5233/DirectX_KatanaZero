#include "PreCompile.h"
#include "HeadHunter_Phase1.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "MainCamera.h"
#include "SlidingDoor.h"

AHeadHunter_Phase1::AHeadHunter_Phase1()
{
}

AHeadHunter_Phase1::~AHeadHunter_Phase1()
{
}

void AHeadHunter_Phase1::BeginPlay()
{
	Super::BeginPlay();	
}

void AHeadHunter_Phase1::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 100.0f;

	ColMap->SetColMapSprite(ImgRes::headhunter_colmap1, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::headhunter_background1, 2.0f, true);
	ColMap->SetBGSpritePosition({ 672.0f, 360.0f, 0.0f });
	
	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 20.f, 175.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);
	Player->SetIntroRunTime(0.9f);

	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);

	AllSlidingDoor.reserve(DoorNum);
	for (int i = 0; i < DoorNum; i++)
	{
		AllSlidingDoor.push_back(GetWorld()->SpawnActor<ASlidingDoor>("SlidingDoor"));
		AllSlidingDoor[i]->SetActive(false);
	}

	State.ChangeState(BossLevelState::transition_off);
}

void AHeadHunter_Phase1::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AHeadHunter_Phase1::LevelReStart()
{
	Super::LevelReStart();

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 402.f, 175.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);
}

void AHeadHunter_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);



}


