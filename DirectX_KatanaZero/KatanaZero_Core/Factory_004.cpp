#include "PreCompile.h"
#include "Factory_004.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"
#include "CeilLaser.h"
#include "Grunt.h"
#include "Fan.h"
#include "Go.h"

AFactory_004::AFactory_004()
{
}

AFactory_004::~AFactory_004()
{
}

void AFactory_004::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_004::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFactory_004::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 60.0f;
	TotalEnemy = 2;

	FloorY = { 637.0f, 925.0f };

	ColMap->SetColMapSprite(ImgRes::factory_colmap4, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background4, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ -50.0f, 222.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);

	MainCamera->SetPlayer(Player.get());
	MainCamera->SetMapTex(ColMap->GetMapTex().get());
	MainCamera->StateChange(MainCameraState::chaseplayer);

	AllEnemy.reserve(TotalEnemy);
	SpawnEnemy<AGrunt>("Grunt", { 480.0f, 638.0f, 0.0f }, EEngineDir::Right, EnemyState::idle);
	SpawnEnemy<AGrunt>("Grunt", { 690.0f, 638.0f, 0.0f }, EEngineDir::Left, EnemyState::idle);

	AllRecComponent.reserve(2);
	ACeilLaser* NewCeilLaser = SpawnRecComponent<ACeilLaser>("CeilLaser", { 945.0f, 1145.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on).get();
	NewCeilLaser->AddLaserPositionY(-288.0f);
	NewCeilLaser->AddLaserScaleY(288.0f);

	Fan = SpawnRecComponent<AFan>("Fan", { 1376.0f, 1039.0f, 0.0f }, EEngineDir::Right, FanState::idle, EUpdateOrder::Fan);

	USoundManager::GetInst().GetFactoryBGM().On();
	State.ChangeState(PlayLevelState::transition_off);
}

void AFactory_004::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFactory_004::LevelReStart()
{
	Super::LevelReStart();
	
	TotalEnemy = 2;

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 162.0f, 222.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);
	MainCamera->SetPlayer(Player.get());

	AllEnemy.reserve(TotalEnemy);
	SpawnEnemy<AGrunt>("Grunt", { 480.0f, 638.0f, 0.0f }, EEngineDir::Right, EnemyState::idle);
	SpawnEnemy<AGrunt>("Grunt", { 690.0f, 638.0f, 0.0f }, EEngineDir::Left, EnemyState::idle);

	AllRecComponent.reserve(2);
	ACeilLaser* NewCeilLaser = SpawnRecComponent<ACeilLaser>("CeilLaser", { 945.0f, 1145.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on).get();
	NewCeilLaser->AddLaserPositionY(-288.0f);
	NewCeilLaser->AddLaserScaleY(288.0f);

	Fan = SpawnRecComponent<AFan>("Fan", { 1376.0f, 1039.0f, 0.0f }, EEngineDir::Right, FanState::idle, EUpdateOrder::Fan);
}

void AFactory_004::ChangeStage()
{
	Super::ChangeStage();

	GEngine->ChangeLevel("Factory_005");
}

void AFactory_004::ClearStart()
{
	Super::ClearStart();

	Go->SetRepeatPos({ 500.0f, 140.0f, 0.0f });
	Go->StateChange("Repeat");
}

bool AFactory_004::IsPlayerAbilityOn() const
{
	return Player->IsAbilityOn();
}