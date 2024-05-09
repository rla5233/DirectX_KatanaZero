#include "PreCompile.h"
#include "HeadHunterLevel_Phase2.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "MainCamera.h"
#include "Grenade.h"

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

	AddRefPosX(HH_Phase2_RefPos::mid, 670.0f);
}

void AHeadHunterLevel_Phase2::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 100.0f;

	ColMap->SetColMapSprite(ImgRes::headhunter_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::headhunter_background2, 2.0f, true);
	ColMap->SetBGSpritePosition({ 672.0f, 425.0f, 0.0f });

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 380.0f, 750.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);
	Player->SetIntroType(EIntroType::HeadHunter2);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase2>("HeadHunter", EUpdateOrder::Enemy);
	HeadHunter->SetActorLocation({ 978.0f, 160.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);

	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);

	AllGrenade.reserve(GrenadeNum);
	for (size_t i = 0; i < GrenadeNum; i++)
	{
		AllGrenade.push_back(GetWorld()->SpawnActor<AGrenade>("Grenade", EUpdateOrder::RecComponent));
		PushRecMapCompo(AllGrenade[i]);
	}

	State.ChangeState(BossLevelState::transition_off);

	float IntroTime = 2.5f;
#ifdef _DEBUG
	IntroTime = 4.5f;
#endif // _DEBUG

	DelayCallBack(IntroTime, [=]
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
	Player->SetActorLocation({ 380.0f, 160.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase2>("HeadHunter", EUpdateOrder::Enemy);
	HeadHunter->SetActorLocation({ 978.0f, 160.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::play);

	AllGrenade.reserve(GrenadeNum);
	for (size_t i = 0; i < GrenadeNum; i++)
	{
		AllGrenade.push_back(GetWorld()->SpawnActor<AGrenade>("Grenade", EUpdateOrder::RecComponent));
		PushRecMapCompo(AllGrenade[i]);
	}
}

void AHeadHunterLevel_Phase2::LevelReEnd()
{
	Super::LevelReEnd();

	AllGrenade.clear();
}

void AHeadHunterLevel_Phase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunterLevel_Phase2::SetShootGrenade(
	const FVector& _ShootPos,
	const FVector& _ShootDir,
	float _Speed)
{
	AllGrenade[CurGrenadeIdx]->SetActorLocation(_ShootPos);
	AllGrenade[CurGrenadeIdx]->SetShootDir(_ShootDir);
	AllGrenade[CurGrenadeIdx]->SetShootSpeed(_Speed);
	AllGrenade[CurGrenadeIdx]->StateChange(GrenadeState::shoot);
	GrenadeIdxUpdate();
}
