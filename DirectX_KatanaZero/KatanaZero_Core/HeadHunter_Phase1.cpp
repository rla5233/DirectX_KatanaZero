#include "PreCompile.h"
#include "HeadHunter_Phase1.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "SlidingDoor.h"
#include "MainCamera.h"
#include "HeadHunter.h"

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
	Player->SetIntroType(EIntroType::HeadHunterBegin);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunter>("HeadHunter");
	HeadHunter->SetActorLocation({ 980.0f, 175.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);

	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);

	AllSlidingDoor.reserve(DoorNum);
	for (int i = 0; i < DoorNum; i++)
	{
		AllSlidingDoor.push_back(GetWorld()->SpawnActor<ASlidingDoor>("SlidingDoor"));
		AllSlidingDoor[i]->SetActive(false);
	}

	AllSlidingDoor[0]->SetActorLocation({ 113.0f, 256.0f, 0.0f });
	AllSlidingDoor[1]->SetActorLocation({ 145.0f, 256.0f, 0.0f });
	AllSlidingDoor[2]->SetActorLocation({ 1201.0f, 256.0f, 0.0f });
	AllSlidingDoor[3]->SetActorLocation({ 1233.0f, 256.0f, 0.0f });

	State.ChangeState(BossLevelState::transition_off);

	DelayCallBack(5.0f, [=]
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

	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);
	DelayCallBack(0.5f, [=]
		{
			HeadHunter->SubStateChange(HeadHunterSubState::play);
		}
	);
}

void AHeadHunter_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunter_Phase1::AllSlidingDoorClose()
{
	for (size_t i = 0; i < AllSlidingDoor.size(); i++)
	{
		AllSlidingDoor[i]->StateChange(SlidingDoorState::close);
	}
}


