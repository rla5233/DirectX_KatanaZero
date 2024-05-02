#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "RecMapCompoBase.h"
#include "DefaultPlayer.h"
#include "CeilLaser.h"
#include "CeilGun.h"
#include "EnemyBase.h"
#include "MouseAim.h"
#include "ReplayUI.h"
#include "OutroMsg.h"
#include "Up_HUD.h"
#include "Stair.h"
#include "Door.h"
#include "Go.h"

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

	USpawnManager::SetGameMode(this);

	StateInit();
	
	GrayScaleEffect = GetWorld()->GetLastTarget()->AddEffect<UGrayScaleEffect>();
	WaveEffect = GetWorld()->GetLastTarget()->AddEffect<UWaveEffect>();

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");
	
	DiaTransition = GetWorld()->SpawnActor<ADiamondTransition>("DiaTransition");
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
	Go->Off();
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

	Debug();

	if (UEngineInput::IsPress('1'))
	{
		BrightnessDown(_DeltaTime);
	}
	
	if (UEngineInput::IsPress('2'))
	{
		BrightnessUp(_DeltaTime);
	}
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

// 디버깅 관련
void APlayLevelBase::Debug()
{
	DebugMessageFunction();
}

void APlayLevelBase::DebugMessageFunction()
{
	{
		std::string Msg = std::format("Player_Pos : {}\n", Player->GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player_State : {}\n", Player->GetCurMainState());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnGround : {}\n", Player->IsOnGround(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnPlatForm : {}\n", Player->IsOnPlatForm(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnStairs : {}\n", Player->IsOnStairs(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("IsOnGP_Boundary : {}\n", Player->IsOnGP_Boundary(Player->GetBody()->GetDir()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

// 상태 초기화
void APlayLevelBase::StateInit()
{
	// State 생성
	State.CreateState(PlayLevelState::intro);
	State.CreateState(PlayLevelState::beginplay_effect);
	State.CreateState(PlayLevelState::play);
	State.CreateState(PlayLevelState::clear);
	State.CreateState(PlayLevelState::outro);
	State.CreateState(PlayLevelState::replay);
	State.CreateState(PlayLevelState::player_dead);
	State.CreateState(PlayLevelState::restart);
	State.CreateState(PlayLevelState::transition_on);
	State.CreateState(PlayLevelState::transition_off);

	// State Start 함수 세팅
	State.SetStartFunction(PlayLevelState::intro, [=] {});
	State.SetStartFunction(PlayLevelState::clear, std::bind(&APlayLevelBase::ClearStart, this));
	State.SetStartFunction(PlayLevelState::outro, [=]
		{
			Player->SubStateChange(PlayerSubState::outro);
			HUD->StateChange(HudState::outro);
			Go->StateChange(GoState::outro);
			GetWorld()->SpawnActor<AOutroMsg>("OutroMsg");
			UContentsHelper::ResetTimeScale();
		}
	);

	State.SetStartFunction(PlayLevelState::beginplay_effect, [=]
		{
			WaveEffect->SetEffectType(EWaveEffectType::BeginPlay);
			WaveEffect->Active(true);

			DelayCallBack(0.2f, [=]
				{
					WaveEffect->ResetTime();
					WaveEffect->Active(false);

					Player->SubStateChange(PlayerSubState::play);
					Player->SetIsPlayValue(true);
					Player->InputOn();

					State.ChangeState(PlayLevelState::play); 
					return;
				}
			);
		}
	);

	State.SetStartFunction(PlayLevelState::play, [=]
		{
			if (nullptr == HUD)
			{
				HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");
			}

			HUD->Reset();
			HUD->On();
			Player->SetRecordingActive(true);

			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->SetRecordingActive(true);
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->SetRecordingActive(true);
			}

			Aim->StateChange(MouseAimState::play);

			DelayCallBack(TotalPlayTime, [=]
				{
					Player->HitByEnemy(EEnemyType::TimeOut);
				}
			);
		}
	);

	State.SetStartFunction(PlayLevelState::replay, [=]
		{ 
			// Recording Off
			Player->SubStateChange(PlayerSubState::replay);

			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->StateChange(EnemyState::replay);
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->StateChange(RecCompoState::replay);
			}

			Aim->StateChange(MouseAimState::replay);

			GrayScaleEffect->Active(true);

			if (nullptr == ReplayUI)
			{
				ReplayUI = GetWorld()->SpawnActor<AReplayUI>("Replay_UI");
			}
			ReplayUI->On();
			InputOn();
		}
	);

	State.SetStartFunction(PlayLevelState::player_dead, [=] 
		{
			// Recording Off
			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->SetRecordingActive(false);
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->SetRecordingActive(false);
			}
		}
	);

	State.SetStartFunction(PlayLevelState::restart, [=] 
		{
			if (nullptr != HUD)
			{
				HUD->Off();
			}

			if (nullptr != Go)
			{
				Go->Off();
			}

			Player->SubStateChange(PlayerSubState::restart);

			for (size_t i = 0; i < AllEnemy.size(); i++)
			{
				AllEnemy[i]->StateChange(EnemyState::restart);
			}

			for (size_t i = 0; i < AllRecComponent.size(); i++)
			{
				AllRecComponent[i]->StateChange(RecCompoState::restart);
			}

			WaveEffect->SetEffectType(EWaveEffectType::Restart);
			WaveEffect->Active(true);
		}
	);

	State.SetStartFunction(PlayLevelState::transition_on, [=] 
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

			ReplayUI->Off();

			DiaTransition->StateChange(DiaTransitionState::on);
		}
	);

	State.SetStartFunction(PlayLevelState::transition_off, [=] 
		{
			DiaTransition->StateChange(DiaTransitionState::off);
		}
	);


	// State Update 함수 세팅
	State.SetUpdateFunction(PlayLevelState::outro, [=](float _DeltaTime) {});
	State.SetUpdateFunction(PlayLevelState::player_dead, [=](float _DeltaTime) 
		{ 	
			if (UEngineInput::IsDown('R'))
			{
				State.ChangeState(PlayLevelState::restart);
			} 
		}
	);

	State.SetUpdateFunction(PlayLevelState::intro, [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
		}
	);

	State.SetUpdateFunction(PlayLevelState::beginplay_effect, [=](float _DeltaTime)
		{
			WaveEffect->Update(_DeltaTime);
		}
	);

	State.SetUpdateFunction(PlayLevelState::play, [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
			if (true == IsStageClear())
			{
				State.ChangeState(PlayLevelState::clear);
				return;
			}

			if (UEngineInput::IsDown('R'))
			{
				State.ChangeState(PlayLevelState::restart);
			}
		}
	);

	State.SetUpdateFunction(PlayLevelState::clear, [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
			if (true == IsRelayStart())
			{
				State.ChangeState(PlayLevelState::outro);
				return;
			}

			if (UEngineInput::IsDown('R'))
			{
				State.ChangeState(PlayLevelState::restart);
			}
		}
	);

	State.SetUpdateFunction(PlayLevelState::replay, [=](float _DeltaTime)
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());

			if (true == IsDown(VK_RBUTTON))
			{
				InputOff();
				State.ChangeState(PlayLevelState::transition_on);
				return;
			}
		}
	);

	State.SetUpdateFunction(PlayLevelState::restart, [=](float _DeltaTime) 
		{
			MainCamera->PlayLevelChaseActor(ColMap->GetMapTex(), Player->GetActorLocation());
			WaveEffect->Update(_DeltaTime);

			if (Player->IsRewindEnd())
			{
				LevelReEnd();
				LevelReStart();
				
				WaveEffect->Active(false);
				WaveEffect->ResetTime();
				
				State.ChangeState(PlayLevelState::beginplay_effect);
				return;
			}
		}
	);

	State.SetUpdateFunction(PlayLevelState::transition_on, [=](float _DeltaTime) 
		{
			if (true == DiaTransition->IsTransitionEnd())
			{
				ChangeStage();
				return;
			}			
		}
	);
	
	State.SetUpdateFunction(PlayLevelState::transition_off, [=](float _DeltaTime) 
		{
			if (true == DiaTransition->IsTransitionEnd())
			{
				State.ChangeState(PlayLevelState::intro);

				Player->StateChange(PlayerState::none);
				Player->SubStateChange(PlayerSubState::intro);

				return;
			}
		}
	);

	// State End 함수 세팅
}

void APlayLevelBase::ClearStart()
{
	if (nullptr == Go)
	{
		Go = GetWorld()->SpawnActor<AGo>("Go");
	}

	Go->On();
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
	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		ACeilLaser* Laser = dynamic_cast<ACeilLaser*>(AllRecComponent[i].get());

		if (nullptr != Laser)
		{
			Laser->StateChange(CeilLaserState::on);
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
	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		ACeilLaser* Laser = dynamic_cast<ACeilLaser*>(AllRecComponent[i].get());

		if (nullptr != Laser)
		{
			Laser->StateChange(CeilLaserState::off);
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
		BrightnessUpEnd = true;
	}

	if (1.0f < EnemyBrightness.X && 1.0f < EnemyBrightness.Y && 1.0f < EnemyBrightness.Z)
	{
		EnemyBrightness = float4::One;
	}

	ColMap->GetBackGround()->SetMulColor(Brightness);

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->GetBody()->SetMulColor(Brightness);
	}

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->GetBody()->SetMulColor(EnemyBrightness);
	}
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
		BrightnessDownEnd = true;
	}

	ColMap->GetBackGround()->SetMulColor(Brightness);

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->GetBody()->SetMulColor(Brightness);
	}

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

FVector APlayLevelBase::GetPlayerLocation() const
{
	return Player->GetActorLocation();
}

int APlayLevelBase::GetPlayerFloorNum() const
{
	return Player->GetFloorNum();
}
