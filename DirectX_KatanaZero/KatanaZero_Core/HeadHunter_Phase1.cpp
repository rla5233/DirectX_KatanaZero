#include "PreCompile.h"
#include "HeadHunter_Phase1.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "SlidingDoor.h"
#include "MainCamera.h"
#include "Mine.h"

#include "HeadHunterBase.h"
#include "HeadHunterPhase1.h"

AHeadHunter_Phase1::AHeadHunter_Phase1()
{
}

AHeadHunter_Phase1::~AHeadHunter_Phase1()
{
}

void AHeadHunter_Phase1::BeginPlay()
{
	Super::BeginPlay();	

	AddRefPosX(HH_Phase1_RefPos::leftfirst, 350.0f);
	AddRefPosX(HH_Phase1_RefPos::leftsecond, 595.0f);
	AddRefPosX(HH_Phase1_RefPos::mid, 690.0f);
	AddRefPosX(HH_Phase1_RefPos::rightsecond, 785.0f);
	AddRefPosX(HH_Phase1_RefPos::rightfirst, 1030.0f);
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

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase1>("HeadHunter", EUpdateOrder::Enemy);
	HeadHunter->SetActorLocation({ 980.0f, 175.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);

	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);

	AllSlidingDoor.reserve(SlidingDoorNum);
	for (int i = 0; i < SlidingDoorNum; i++)
	{
		AllSlidingDoor.push_back(GetWorld()->SpawnActor<ASlidingDoor>("SlidingDoor", EUpdateOrder::RecComponent));
		AllSlidingDoor[i]->SetActive(false);
		PushRecMapCompo(AllSlidingDoor[i]);
	}

	AllSlidingDoor[0]->SetActorLocation({ 113.0f, 256.0f, 0.0f });
	AllSlidingDoor[1]->SetActorLocation({ 145.0f, 256.0f, 0.0f });
	AllSlidingDoor[2]->SetActorLocation({ 1201.0f, 256.0f, 0.0f });
	AllSlidingDoor[3]->SetActorLocation({ 1233.0f, 256.0f, 0.0f });

	AllMine.reserve(MineNum);
	for (int i = 0; i < MineNum; i++)
	{
		AllMine.push_back(GetWorld()->SpawnActor<AMine>("GroundMine", EUpdateOrder::RecComponent));
		AllMine[i]->SetActorLocation({ 53.0f + MineInterVal * i, 182.0f, 0.0f });
		PushRecMapCompo(AllMine[i]);
	}

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

	AllSlidingDoor.clear();
}

void AHeadHunter_Phase1::LevelReStart()
{
	Super::LevelReStart();

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 402.f, 175.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase1>("HeadHunter", EUpdateOrder::Enemy);
	HeadHunter->SetActorLocation({ 980.0f, 175.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::play);

	AllSlidingDoor.reserve(SlidingDoorNum);
	for (int i = 0; i < SlidingDoorNum; i++)
	{
		AllSlidingDoor.push_back(GetWorld()->SpawnActor<ASlidingDoor>("SlidingDoor", EUpdateOrder::RecComponent));
		AllSlidingDoor[i]->StateChange(SlidingDoorState::closed);
		PushRecMapCompo(AllSlidingDoor[i]);
	}

	AllSlidingDoor[0]->SetActorLocation({ 113.0f, 256.0f, 0.0f });
	AllSlidingDoor[1]->SetActorLocation({ 145.0f, 256.0f, 0.0f });
	AllSlidingDoor[2]->SetActorLocation({ 1201.0f, 256.0f, 0.0f });
	AllSlidingDoor[3]->SetActorLocation({ 1233.0f, 256.0f, 0.0f });

	AllMine.reserve(MineNum);
	for (int i = 0; i < MineNum; i++)
	{
		AllMine.push_back(GetWorld()->SpawnActor<AMine>("GroundMine", EUpdateOrder::RecComponent));
		AllMine[i]->SetActorLocation({ 53.0f + MineInterVal * i, 182.0f, 0.0f });
		PushRecMapCompo(AllMine[i]);
	}
}

void AHeadHunter_Phase1::LevelReEnd()
{
	Super::LevelReEnd();

	AllSlidingDoor.clear();
	AllMine.clear();
}

bool AHeadHunter_Phase1::IsStageClear()
{
	return HeadHunter->IsDead();
}

void AHeadHunter_Phase1::ClearStart()
{
	AllMineOn();
}

void AHeadHunter_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

FVector AHeadHunter_Phase1::FindExitDoor()
{
	float CurPlayerPosX = Player->GetActorLocation().X;
	
	float Door0 = abs(DoorPosX[0] - CurPlayerPosX);
	float Door3 = abs(DoorPosX[3] - CurPlayerPosX);

	FVector Door0_Pos = { DoorPosX[0], 175.0f, 0.0f };
	FVector Door3_Pos = { DoorPosX[3], 175.0f, 0.0f };

	return Door0 < Door3 ? Door3_Pos : Door0_Pos;
}

void AHeadHunter_Phase1::AllSlidingDoorClose()
{
	for (size_t i = 0; i < AllSlidingDoor.size(); i++)
	{
		AllSlidingDoor[i]->StateChange(SlidingDoorState::close);
	}
}

void AHeadHunter_Phase1::AllMineOn()
{
	for (size_t i = 0; i < AllMine.size(); i++)
	{
		AllMine[i]->StateChange(MineState::on);
	}
}


