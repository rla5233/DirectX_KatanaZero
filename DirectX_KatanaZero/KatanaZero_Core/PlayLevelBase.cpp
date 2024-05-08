#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "CeilLaser.h"
#include "CeilGun.h"
#include "EnemyBase.h"
#include "MouseAim.h"
#include "ReplayUI.h"
#include "Up_HUD.h"
#include "Stair.h"
#include "Door.h"
#include "Go.h"

#include "OutroMsg.h"
#include "FailedMsg.h"

#include "GrayScaleEffect.h"
#include "WaveEffect.h"
#include "DiamondTransition.h"

APlayLevelBase::APlayLevelBase()
{
}
APlayLevelBase::~APlayLevelBase()
{
}

void APlayLevelBase::BeginPlay()
{
	Super::BeginPlay();

	UPlayLevelSpawnManager::SetGameMode(this);

	StateInit();
	
	GrayScaleEffect = GetWorld()->GetLastTarget()->AddEffect<UGrayScaleEffect>();
	WaveEffect = GetWorld()->GetLastTarget()->AddEffect<UWaveEffect>();
	DiaTransition = GetWorld()->SpawnActor<ADiamondTransition>("DiaTransition");

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");

	ReplayUI = GetWorld()->SpawnActor<AReplayUI>("Replay_UI");
	FailedMsg = GetWorld()->SpawnActor<AFailedMsg>("FailedMsg");
	OutroMsg = GetWorld()->SpawnActor<AOutroMsg>("OutroMsg");
}

void APlayLevelBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	MainCamera = GetWorld()->SpawnActor<AMainCamera>("ContentsMainCamera");
	ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");

	GrayScaleEffect->Active(false);
	WaveEffect->Active(false);
}

void APlayLevelBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	ColMap->Destroy();
	Player->Destroy();
	Player->SetIsPlayValue(false);
	MainCamera->Destroy();

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->Destroy();
		AllEnemy[i] = nullptr;
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->Destroy();
		AllRecComponent[i] = nullptr;
	}

	for (size_t i = 0; i < AllDoor.size(); i++)
	{
		for (size_t j = 0; j < AllDoor[i].size(); j++)
		{
			AllDoor[i][j]->Destroy();
			AllDoor[i][j] = nullptr;
		}

		AllDoor[i].clear();
	}

	for (size_t i = 0; i < AllStair.size(); i++)
	{
		for (size_t j = 0; j < AllStair[i].size(); j++)
		{
			AllStair[i][j]->Destroy();
			AllStair[i][j] = nullptr;
		}

		AllStair[i].clear();
	}

	ColMap		= nullptr;
	Player		= nullptr;
	MainCamera	= nullptr;

	AllDoor.clear();
	AllStair.clear();
	AllEnemy.clear();
	AllRecComponent.clear();

	// UI
	HUD->Off();

	if (nullptr != Go)
	{
		Go->Off();
	}

	ReplayUI->Off();
}

void APlayLevelBase::LevelReEnd()
{
	Player->Destroy();
	Player->SetIsPlayValue(false);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->Destroy();
		AllEnemy[i] = nullptr;
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->Destroy();
		AllRecComponent[i] = nullptr;
	}

	Player = nullptr;

	AllEnemy.clear();
	AllRecComponent.clear();
}

void APlayLevelBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

bool APlayLevelBase::IsStageClear()
{
	bool Result = false;

	if (0 == TotalEnemy)
	{
		Result = true;
	}

	return Result;
}

bool APlayLevelBase::IsRelayStart()
{
	if (true == Player->IsDead())
	{
		return false;
	}

	bool Result = false;

	std::shared_ptr<UEngineTexture> MapTex = ColMap->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector PlayerPos = Player->GetActorLocation();

	PlayerPos.Y = MapTexScale.Y - (PlayerPos.Y + 5.0f);

	Color8Bit PixelColor = MapTex->GetColor(PlayerPos, Color8Bit::Black);

	if (ColMap::RED == PixelColor)
	{
		Result = true;
	}

	return Result;
}

void APlayLevelBase::SetReplay()
{
	ResetReplaySpeed();

	Player->SetReplayMode(EReplayMode::Play);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Play);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Play);
	}
}

void APlayLevelBase::SetReplayStop()
{
	Player->SetReplayMode(EReplayMode::Stop);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Stop);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Stop);
	}
}

void APlayLevelBase::SetRewind()
{
	ResetReplaySpeed();

	Player->SetReplayMode(EReplayMode::Rewind);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Rewind);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Rewind);
	}
}

void APlayLevelBase::ResetReplaySpeed()
{
	Player->SetReplaySpeed(1);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplaySpeed(1);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplaySpeed(1);
	}
}

void APlayLevelBase::IncreaseReplaySpeed()
{
	Player->IncreaseReplaySpeed();

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->IncreaseReplaySpeed();
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->IncreaseReplaySpeed();
	}
}

void APlayLevelBase::PanicSwitchOn()
{
	bool IsLaserOnSound = false;

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		ACeilLaser* Laser = dynamic_cast<ACeilLaser*>(AllRecComponent[i].get());

		if (nullptr != Laser)
		{
			Laser->StateChange(CeilLaserState::on);

			if (false == IsLaserOnSound)
			{
				UEngineSound::SoundPlay(SoundRes::ceil_laser_on);
				IsLaserOnSound = true;
			}
			continue;
		}

		ACeilGun* Gun = dynamic_cast<ACeilGun*>(AllRecComponent[i].get());

		if (nullptr != Gun)
		{
			Gun->StateChange(CeilGunState::on);
			continue;
		}
	}
}

void APlayLevelBase::PanicSwitchOff()
{
	bool IsLaserOffSound = false;

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		ACeilLaser* Laser = dynamic_cast<ACeilLaser*>(AllRecComponent[i].get());

		if (nullptr != Laser)
		{
			Laser->StateChange(CeilLaserState::off);
			
			if (false == IsLaserOffSound)
			{
				UEngineSound::SoundPlay(SoundRes::ceil_laser_off);
				IsLaserOffSound = true;
			}
			continue;
		}

		ACeilGun* Gun = dynamic_cast<ACeilGun*>(AllRecComponent[i].get());

		if (nullptr != Gun)
		{
			Gun->StateChange(CeilGunState::off);
			continue;
		}
	}
}

bool APlayLevelBase::IsReplayEnd() const
{
	return Player->IsReplayEnd();
}

bool APlayLevelBase::IsRewindEnd() const
{
	return Player->IsRewindEnd();
}

void APlayLevelBase::BrightnessUp(float _DeltaTime)
{
	if (true == BrightnessUpEnd)
	{
		return;
	}

	Brightness.X += _DeltaTime;
	Brightness.Y += _DeltaTime;
	Brightness.Z += _DeltaTime;

	EnemyBrightness.X += _DeltaTime;
	EnemyBrightness.Y += _DeltaTime;
	EnemyBrightness.Z += _DeltaTime;
	BrightnessDownEnd = false;

	if (1.0f < Brightness.X && 1.0f < Brightness.Y && 1.0f < Brightness.Z)
	{
		Brightness = float4::One;
		PlayerBrightness = { 1.0f, 1.0f, 1.0f };
		BrightnessUpEnd = true;
	}

	if (1.0f < EnemyBrightness.X && 1.0f < EnemyBrightness.Y && 1.0f < EnemyBrightness.Z)
	{
		EnemyBrightness = float4::One;
	}

	ColMap->GetBackGround()->SetMulColor(Brightness);

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetAllMulColor(Brightness);
	}

	// Enemy
	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->GetBody()->SetMulColor(EnemyBrightness);
	}

	// Player
	PlayerBrightness.Y -= PlayerBrightWeight * _DeltaTime;
	PlayerBrightness.Z -= PlayerBrightWeight * _DeltaTime;

	if (1.0f > PlayerBrightness.Y && 1.0f > PlayerBrightness.Z)
	{
		PlayerBrightness.Y = 1.0f;
		PlayerBrightness.Z = 1.0f;
	}

	Player->GetBody()->SetMulColor(PlayerBrightness);
}

void APlayLevelBase::BrightnessDown(float _DeltaTime)
{
	if (true == BrightnessDownEnd)
	{
		return;
	}

	Brightness.X -= _DeltaTime;
	Brightness.Y -= _DeltaTime;
	Brightness.Z -= _DeltaTime;
	BrightnessUpEnd = false;

	if (0.2f > Brightness.X && 0.2f > Brightness.Y && 0.2f > Brightness.Z)
	{
		Brightness = { 0.2f, 0.2f, 0.2f };
		PlayerBrightness = { 1.0f, 6.0f, 6.0f };
		BrightnessDownEnd = true;
	}

	ColMap->GetBackGround()->SetMulColor(Brightness);

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetAllMulColor(Brightness);
	}

	// Enemy
	EnemyBrightness.X -= _DeltaTime;
	EnemyBrightness.Y -= _DeltaTime;
	EnemyBrightness.Z -= _DeltaTime;

	if (0.5f > EnemyBrightness.X && 0.5f > EnemyBrightness.Y && 0.5f > EnemyBrightness.Z)
	{
		EnemyBrightness = { 0.5f, 0.5f, 0.5f };
	}

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->GetBody()->SetMulColor(EnemyBrightness);
	}

	// Player
	PlayerBrightness.Y += PlayerBrightWeight * _DeltaTime;
	PlayerBrightness.Z += PlayerBrightWeight * _DeltaTime;

	if (6.0f < PlayerBrightness.Y && 6.0f < PlayerBrightness.Z)
	{
		PlayerBrightness.Y = 6.0f;
		PlayerBrightness.Z = 6.0f;
	}

	Player->GetBody()->SetMulColor(PlayerBrightness);
}

void APlayLevelBase::BatterPartUpdate(float _AbilityTime)
{
	HUD->BatteryPartUpdate(_AbilityTime);
}

int APlayLevelBase::FloorCheck(float _PosY)
{
	if (0 == FloorY.size())
	{
		return 0;
	}

	int Result = -1;
	int FloorSize = static_cast<int>(FloorY.size());

	if (FloorY[0] > _PosY)
	{
		Result = 0;
		return Result;
	}

	if (FloorY[FloorSize - 1] <= _PosY)
	{
		Result = FloorSize;
		return Result;
	}

	for (int i = 1; i <= FloorSize - 1; i++)
	{
		if (FloorY[i - 1] <= _PosY && FloorY[i] > _PosY)
		{
			Result = i;
		}
	}

	return Result;
}

bool APlayLevelBase::IsCloseDoor(float _StartX, float _EndX, int _FloorNum)
{
	bool Result = false;

	if (true == AllDoor.empty() || true == AllDoor[_FloorNum].empty())
	{
		return false;
	}

	for (size_t i = 0; i < AllDoor[_FloorNum].size(); i++)
	{
		float DoorX = AllDoor[_FloorNum][i]->GetActorLocation().X;

		if (DoorState::close == AllDoor[_FloorNum][i]->GetCurState())
		{
			if (_StartX < DoorX && _EndX > DoorX)
			{
				Result = true;
			}
			else if (_EndX < DoorX && _StartX > DoorX)
			{
				Result = true;
			}
		}
	}

	return Result;
}

AStair* APlayLevelBase::FindStair(EStairType _StairType, int _FloorNum) const
{
	AStair* Result = nullptr;

	if (false == AllStair.empty() && false == AllStair[_FloorNum].empty())
	{
		for (size_t i = 0; i < AllStair[_FloorNum].size(); i++)
		{
			if (_StairType == AllStair[_FloorNum][i]->GetStairType())
			{
				Result = AllStair[_FloorNum][i].get();
			}
		}
	}


	return Result;
}

bool APlayLevelBase::IsPlayerDead() const
{
	return PlayerState::dead == Player->GetCurMainState();
}

FVector APlayLevelBase::GetPlayerLocation() const
{
	return Player->GetActorLocation();
}

int APlayLevelBase::GetPlayerFloorNum() const
{
	return Player->GetFloorNum();
}

void APlayLevelBase::PushRecMapCompo(std::shared_ptr<ARecMapCompoBase> _RecCompo)
{
	AllRecComponent.push_back(_RecCompo);
}