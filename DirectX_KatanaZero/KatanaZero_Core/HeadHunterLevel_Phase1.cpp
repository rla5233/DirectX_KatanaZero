#include "PreCompile.h"
#include "HeadHunterLevel_Phase1.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "SlidingDoor.h"
#include "MainCamera.h"
#include "UnderBlack.h"
#include "Mine.h"
#include "Up_HUD.h"

#include "HeadHunterBase.h"
#include "HeadHunterPhase1.h"

AHeadHunterLevel_Phase1::AHeadHunterLevel_Phase1()
{
}

AHeadHunterLevel_Phase1::~AHeadHunterLevel_Phase1()
{
}

void AHeadHunterLevel_Phase1::BeginPlay()
{
	Super::BeginPlay();	

	AddRefPos(HH_Phase1_RefPos::leftfirst, 350.0f);
	AddRefPos(HH_Phase1_RefPos::leftsecond, 595.0f);
	AddRefPos(HH_Phase1_RefPos::mid, 690.0f);
	AddRefPos(HH_Phase1_RefPos::rightsecond, 785.0f);
	AddRefPos(HH_Phase1_RefPos::rightfirst, 1030.0f);
}

void AHeadHunterLevel_Phase1::LevelStart(ULevel* _PrevLevel)
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
	Player->SetIntroType(EIntroType::HeadHunter1);

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

	UnderBlack = GetWorld()->SpawnActor<AUnderBlack>("UnderBlack", EUpdateOrder::RecComponent);
	UnderBlack->SetActorLocation({ 672.0f, 150.0f, 0.0f });
	UnderBlack->StateChange(UnderBlackState::none);
	PushRecMapCompo(UnderBlack);

	State.ChangeState(BossLevelState::transition_off);

	DelayCallBack(5.0f, [=]
		{
			Player->StateChange(PlayerState::idle);
			Player->SubStateChange(PlayerSubState::none);
			
			USoundManager::GetInst()->ResetHeadHunterBGM1();
			USoundManager::GetInst()->GetHeadHunterBGM1().On();

			DelayCallBack(0.8f, [=]
				{
					HeadHunter->SubStateChange(HeadHunterSubState::play);
				}
			);
		}
	);
}

void AHeadHunterLevel_Phase1::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	AllSlidingDoor.clear();
	USoundManager::GetInst()->GetHeadHunterBGM1().Off();
}

void AHeadHunterLevel_Phase1::LevelReStart()
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

	UnderBlack = GetWorld()->SpawnActor<AUnderBlack>("UnderBlack", EUpdateOrder::RecComponent);
	UnderBlack->SetActorLocation({ 672.0f, 150.0f, 0.0f });
	UnderBlack->StateChange(UnderBlackState::none);
	PushRecMapCompo(UnderBlack);
}

void AHeadHunterLevel_Phase1::LevelReEnd()
{
	Super::LevelReEnd();

	AllSlidingDoor.clear();
	AllMine.clear();
}

bool AHeadHunterLevel_Phase1::IsStageClear()
{
	return HeadHunter->IsDead();
}

void AHeadHunterLevel_Phase1::ChangeStage()
{
	Super::ChangeStage();

	GEngine->ChangeLevel("HeadHunter_Phase2");
}

void AHeadHunterLevel_Phase1::ClearStart()
{
	AllMineOn();

	float inter = 0.1f;
	for (int i = 0; i < 8; i++)
	{
		DelayCallBack(1.0f + inter * i, [=]
			{
				UEngineSound::SoundPlay(SoundRes::hh_explosion);
			}
		);
	}
}

void AHeadHunterLevel_Phase1::Clear(float _DeltaTime)
{
	if (0.0f > PlayTimeCount)
	{
		Player->HitByEnemy(FVector::Zero, EEnemyType::TimeOut);
		return;
	}

	if (-500.0f > Player->GetActorLocation().Y)
	{
		HUD->StateChange(HudState::outro);
		State.ChangeState(PlayLevelState::transition_on);
		return;
	}

	if (UEngineInput::IsDown('R'))
	{
		State.ChangeState(PlayLevelState::restart);
		return;
	}

	if (0.0f > Player->GetVelocity().Y
		&& false == Player->IsDead()
		&& true == UnderBlack->GetBody()->IsActive())
	{
		Player->StateChange(PlayerState::onlyfall);
		return;
	}

	PlayTimeCount -= _DeltaTime;
}

void AHeadHunterLevel_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

FVector AHeadHunterLevel_Phase1::FindExitDoor()
{
	float CurPlayerPosX = Player->GetActorLocation().X;
	
	float Door0 = abs(DoorPosX[0] - CurPlayerPosX);
	float Door3 = abs(DoorPosX[3] - CurPlayerPosX);

	FVector Door0_Pos = { DoorPosX[0], 175.0f, 0.0f };
	FVector Door3_Pos = { DoorPosX[3], 175.0f, 0.0f };

	return Door0 < Door3 ? Door3_Pos : Door0_Pos;
}

void AHeadHunterLevel_Phase1::AllSlidingDoorClose()
{
	for (size_t i = 0; i < AllSlidingDoor.size(); i++)
	{
		AllSlidingDoor[i]->StateChange(SlidingDoorState::close);
	}

	UEngineSound::SoundPlay(SoundRes::blastdoor_close);
}

void AHeadHunterLevel_Phase1::AllMineOn()
{
	for (size_t i = 0; i < AllMine.size(); i++)
	{
		AllMine[i]->StateChange(MineState::on);
		float Inter = 0.022f * i;
		DelayCallBack(1.0f + Inter, [=] 
			{ 
				if (PlayLevelState::restart == State.GetCurStateName())
				{
					return;
				}

				if (0 == i)
				{
					Player->SetJumpSpeedWeight(1.75f);
					GEngine->SetGlobalTimeScale(0.1f);
				}
				else if(1 == i)
				{
					GEngine->SetGlobalTimeScale(1.0f);
				}
				else if (16 == i)
				{
					UnderBlack->StateChange(UnderBlackState::on);
				}

				AllMine[i]->StateChange(MineState::explode); 
			}
		);
	}
}


