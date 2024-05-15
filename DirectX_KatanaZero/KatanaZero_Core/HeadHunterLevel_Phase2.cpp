#include "PreCompile.h"
#include "HeadHunterLevel_Phase2.h"

#include "DefaultPlayer.h"
#include "ColMapObject.h"
#include "MainCamera.h"
#include "WallTurret.h"
#include "MouseAim.h"
#include "Grenade.h"
#include "Bullet.h"
#include "Laser.h"
#include "Up_HUD.h"
#include "HeadHunterHead.h"

#include "HeadHunterPhase2.h"

const int AHeadHunterLevel_Phase2::BulletNum = 22;

AHeadHunterLevel_Phase2::AHeadHunterLevel_Phase2()
{
}

AHeadHunterLevel_Phase2::~AHeadHunterLevel_Phase2()
{
}

void AHeadHunterLevel_Phase2::BeginPlay()
{
	Super::BeginPlay();

	AddRefPos(HH_Phase2_RefPos::leftwall, 230.0f);
	AddRefPos(HH_Phase2_RefPos::mid, 670.0f);
	AddRefPos(HH_Phase2_RefPos::rightwall, 1114.0f);

	AddRefPos(HH_Phase2_RefPos::ground, 160.0f);
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

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase2>("HeadHunter", EUpdateOrder::HeadHunter);
	HeadHunter->SetActorLocation({ 978.0f, 160.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);

	MainCamera->SetActorLocation({ 672.0f, 360.0f, -100.0f });
	MainCamera->SetRetShakePos({ 672.0f, 360.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);

	AllGrenade.reserve(GrenadeNum);
	for (size_t i = 0; i < GrenadeNum; i++)
	{
		AllGrenade.push_back(GetWorld()->SpawnActor<AGrenade>("Grenade", EUpdateOrder::RecComponent));
		PushRecMapCompo(AllGrenade[i]);
	}

	AllBullet.reserve(BulletNum);
	for (size_t i = 0; i < BulletNum; i++)
	{
		AllBullet.push_back(GetWorld()->SpawnActor<ABullet>("Bullet", EUpdateOrder::RecComponent));
		PushRecMapCompo(AllBullet[i]);
	}

	WallTurret = GetWorld()->SpawnActor<AWallTurret>("WallTurret", EUpdateOrder::RecComponent);
	WallTurret->SetActorLocation({ 183.0f, 355.0f, 0.0f });
	PushRecMapCompo(WallTurret);

	State.ChangeState(BossLevelState::transition_off);

	float IntroTime = 2.5f;
#ifdef _DEBUG
	IntroTime = 4.5f;
#endif // _DEBUG

	DelayCallBack(IntroTime, [=]
		{
			Player->StateChange(PlayerState::idle);
			Player->SubStateChange(PlayerSubState::none);

			USoundManager::GetInst()->ResetHeadHunterBGM2();
			USoundManager::GetInst()->GetHeadHunterBGM2().On();

			DelayCallBack(1.0f, [=]
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

	HeadHunterHead->Destroy();
	HeadHunterHead = nullptr;
	USoundManager::GetInst()->GetHeadHunterBGM2().Off();
}

void AHeadHunterLevel_Phase2::LevelReStart()
{
	Super::LevelReStart();

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 380.0f, 160.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);

	HeadHunter = GetWorld()->SpawnActor<AHeadHunterPhase2>("HeadHunter", EUpdateOrder::HeadHunter);
	HeadHunter->SetActorLocation({ 978.0f, 160.0f, 0.0f });
	HeadHunter->SetDir(EEngineDir::Left);
	HeadHunter->StateChange(HeadHunterState::idle);
	HeadHunter->SubStateChange(HeadHunterSubState::wait);

	DelayCallBack(0.5f, [=]
		{
			HeadHunter->SubStateChange(HeadHunterSubState::play);
		}
	);

	AllGrenade.reserve(GrenadeNum);
	for (size_t i = 0; i < GrenadeNum; i++)
	{
		AllGrenade.push_back(GetWorld()->SpawnActor<AGrenade>("Grenade", EUpdateOrder::RecComponent));
		PushRecMapCompo(AllGrenade[i]);
	}

	AllBullet.reserve(BulletNum);
	for (size_t i = 0; i < BulletNum; i++)
	{
		AllBullet.push_back(GetWorld()->SpawnActor<ABullet>("Bullet", EUpdateOrder::RecComponent));
		PushRecMapCompo(AllBullet[i]);
	}

	WallTurret = GetWorld()->SpawnActor<AWallTurret>("WallTurret", EUpdateOrder::RecComponent);
	WallTurret->SetActorLocation({ 183.0f, 355.0f, 0.0f });
	PushRecMapCompo(WallTurret);

	USoundManager::GetInst()->GetHeadHunterBGM2().SetVolume(0.6f);
}

void AHeadHunterLevel_Phase2::LevelReEnd()
{
	Super::LevelReEnd();

	AllGrenade.clear();
	AllBullet.clear();
}

void AHeadHunterLevel_Phase2::RestartStart()
{
	Super::RestartStart();

	if (nullptr != HeadHunterHead)
	{
		HeadHunterHead->Destroy();
		HeadHunterHead = nullptr;
	}
}

void AHeadHunterLevel_Phase2::ClearStart()
{
	DelayCallBack(4.0f, [=] 
		{ 
			UEngineSound::SoundPlay(SoundRes::bgm_ending).SetVolume(0.25f); 
			EndingFadeOutAlpha = 1.0f;
			IsEndingFadeOut = true;
			ColMap->ColMapOff();
		}
	);

	Player->InputOff();
}

void AHeadHunterLevel_Phase2::Clear(float _DeltaTime)
{
	EndingFadeOut(_DeltaTime);
}

void AHeadHunterLevel_Phase2::EndingFadeOut(float _DeltaTime)
{
	if (true == IsEndingFadeOut)
	{
		float4 MulColor = float4::One;
		MulColor.R = EndingFadeOutAlpha;
		MulColor.G = EndingFadeOutAlpha;
		MulColor.B = EndingFadeOutAlpha;
		EndingFadeOutAlpha -= 0.1f * _DeltaTime;

		if (0.0f > EndingFadeOutAlpha)
		{
			EndingFadeOutAlpha = 0.0f;
			GEngine->ChangeLevel("Ending");
		}

		ColMap->SetMulColor(MulColor);
		HeadHunterHead->GetBody()->SetMulColor(MulColor);
		HeadHunter->GetBody()->SetMulColor(MulColor);
		Player->GetBody()->SetMulColor(MulColor);
		Aim->GetBody()->SetMulColor(MulColor);
		HUD->SetAllMulColor(MulColor);
	}
}

void AHeadHunterLevel_Phase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunterLevel_Phase2::SetShootGrenade(const FVector& _ShootPos, const FVector& _ShootDir, float _Speed)
{
	if (GrenadeState::none != AllGrenade[CurGrenadeIdx]->GetCurState())
	{
		GrenadeIdxUpdate();
	}

	AllGrenade[CurGrenadeIdx]->SetActorLocation(_ShootPos);
	AllGrenade[CurGrenadeIdx]->SetShootDir(_ShootDir);
	AllGrenade[CurGrenadeIdx]->SetShootSpeed(_Speed);
	AllGrenade[CurGrenadeIdx]->StateChange(GrenadeState::shoot);
	GrenadeIdxUpdate();
}

void AHeadHunterLevel_Phase2::SetShootBullet(const FVector& _ShootPos, const FVector& _ShootDir)
{
	if (BulletState::none != AllBullet[CurBulletIdx]->GetCurState())
	{
		BulletIdxUpdate();
	}

	AllBullet[CurBulletIdx]->SetActorLocation(_ShootPos);
	AllBullet[CurBulletIdx]->SetShootDir(_ShootDir);
	AllBullet[CurBulletIdx]->StateChange(BulletState::shoot);
	BulletIdxUpdate();
}

void AHeadHunterLevel_Phase2::SetWallTurret()
{
	WallTurret->StateChange(WallTurretState::open);
}

void AHeadHunterLevel_Phase2::SetHeadHunterHead(const FVector& _Pos, EEngineDir _Dir)
{
	HeadHunterHead = GetWorld()->SpawnActor<AHeadHunterHead>("HeadHunterHead");
	HeadHunterHead->SetActorLocation(_Pos);
	HeadHunterHead->GetBody()->SetDir(_Dir);
	HeadHunterHead->StateChange(HeadState::hurtfly);
}

void AHeadHunterLevel_Phase2::CreateLaser(const FVector& _Pos, float _Deg, float _AlphaDownDelayTime)
{
	ALaser* NewLaser = GetWorld()->SpawnActor<ALaser>("Laser", EUpdateOrder::RecComponent).get();
	NewLaser->SetAlphaDownTimeCount(_AlphaDownDelayTime);
	NewLaser->SetActorLocation(_Pos);
	NewLaser->SetDeg(_Deg);
	NewLaser->StateChange(LaserState::aim);
}
