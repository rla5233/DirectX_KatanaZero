#include "PreCompile.h"
#include "Factory_003.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "CeilLaser.h"
#include "CeilGun.h"
#include "PanicSwitch.h"
#include "Up_HUD.h"
#include "Go.h"

AFactory_003::AFactory_003()
{
}

AFactory_003::~AFactory_003()
{
}

void AFactory_003::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_003::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFactory_003::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 60.0f;
	TotalEnemy = 0;
	
	MainCamera->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap3, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background3, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 10.0f, 259.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);

	AllRecComponent.reserve(10);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 368.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1343.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1905.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1965.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 2025.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 2085.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 2145.0f, 478.0f, 0.0f}, EEngineDir::Left, CeilLaserState::on);

	std::shared_ptr<ACeilGun> NewCeilGun = nullptr;
	NewCeilGun = SpawnRecComponent<ACeilGun>("CeilGun", { 840.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilGunState::on);
	NewCeilGun->SetPointX(655.0f, 1280.0f);
	NewCeilGun->SetVelocity({ -120.0f, 0.0f, 0.0f });

	NewCeilGun = SpawnRecComponent<ACeilGun>("CeilGun", { 1270.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilGunState::on);
	NewCeilGun->SetPointX(655.0f, 1280.0f);
	NewCeilGun->SetVelocity({ -120.0f, 0.0f, 0.0f });

	SpawnRecComponent<APanicSwitch>("PanicSwitch", { 1765.0f, 335.0f, 0.0f}, EEngineDir::Right, PanicSwitchState::on);
}

void AFactory_003::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFactory_003::LevelReStart()
{
	Super::LevelReStart();

	TotalEnemy = 0;

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 222.0f, 259.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);

	AllRecComponent.reserve(10);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 368.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1343.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1905.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1965.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 2025.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 2085.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 2145.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);

	std::shared_ptr<ACeilGun> NewCeilGun = nullptr;
	NewCeilGun = SpawnRecComponent<ACeilGun>("CeilGun", { 840.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilGunState::on);
	NewCeilGun->SetPointX(655.0f, 1280.0f);
	NewCeilGun->SetVelocity({ -120.0f, 0.0f, 0.0f });

	NewCeilGun = SpawnRecComponent<ACeilGun>("CeilGun", { 1270.0f, 478.0f, 0.0f }, EEngineDir::Left, CeilGunState::on);
	NewCeilGun->SetPointX(655.0f, 1280.0f);
	NewCeilGun->SetVelocity({ -120.0f, 0.0f, 0.0f });

	SpawnRecComponent<APanicSwitch>("PanicSwitch", { 1765.0f, 335.0f, 0.0f }, EEngineDir::Right, PanicSwitchState::on);
}

void AFactory_003::ChangeStage()
{
	Super::ChangeStage();

	GEngine->ChangeLevel("Factory_004");
}

void AFactory_003::ClearStart()
{
	Super::ClearStart();

	Go->SetRepeatPos({ 500.0f, 40.0f, 0.0f });
	Go->StateChange("Repeat");
}
