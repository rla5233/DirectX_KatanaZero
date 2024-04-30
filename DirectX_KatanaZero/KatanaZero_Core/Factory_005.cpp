#include "PreCompile.h"
#include "Factory_005.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"
#include "Grunt.h"
#include "GangSter.h"
#include "CeilLaser.h"
#include "PanicSwitch.h"
#include "Scientist.h"
#include "Stair.h"
#include "Door.h"
#include "Go.h"

AFactory_005::AFactory_005()
{
}

AFactory_005::~AFactory_005()
{
}

void AFactory_005::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_005::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 100.0f;
	TotalEnemy = 9;
	FloorY = { 414.0f, 701.0f };

	MainCamera->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap5, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background5, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ -5.0f, 127.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);

	AllEnemy.reserve(TotalEnemy);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 580.0f, 130.0f, 0.0f }, EEngineDir::Right, 3.5f, 5.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 950.0f, 130.0f, 0.0f }, EEngineDir::Left, 3.5f, 5.0f, EnemyState::patrol_stop);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1454.0f, 415.0f, 0.0f }, EEngineDir::Right, 1.8f, 5.0f, EnemyState::patrol_stop);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 247.0f, 704.0f, 0.0f }, EEngineDir::Right, 4.5f, 5.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1111.0f, 704.0f, 0.0f }, EEngineDir::Right, 5.0f, 4.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1633.0f, 704.0f, 0.0f }, EEngineDir::Left, 5.0f, 5.0f, EnemyState::patrol_stop);

	ExtraGangster.reserve(3);
	ExtraGangster.push_back(SpawnEnemy<AGangSter>("Gangster", { 75.0f, 127.0f, 0.0f }, EEngineDir::Right, EnemyState::none).get());
	ExtraGangster.push_back(SpawnEnemy<AGangSter>("Gangster", { 145.0f, 127.0f, 0.0f }, EEngineDir::Right, EnemyState::none).get());
	ExtraGangster.push_back(SpawnEnemy<AGangSter>("Gangster", { 215.0f, 127.0f, 0.0f }, EEngineDir::Right, EnemyState::none).get());

	AllRecComponent.reserve(10);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 657.0f, 634.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 687.0f, 634.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 754.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 784.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1713.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1743.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1743.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);

	SpawnRecComponent<APanicSwitch>("PanicSwitch", { 1165.0f, 795.0f, 0.0f }, EEngineDir::Right, PanicSwitchState::on);
	SpawnRecComponent<AScientist>("Scientist", { 1910.0f, 703.0f, 0.0f }, EEngineDir::Left, ScientistState::idle);

	AllDoor.resize(3);
	{
		std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 527.0f, 192.0f, 0.0f }, EEngineDir::Right, DoorState::close);
		AllDoor[0].push_back(NewDoor);
	}

	{
		std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 1422.0f, 480.0f, 0.0f }, EEngineDir::Right, DoorState::close);
		AllDoor[1].push_back(NewDoor);
	}

	{
		std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 1070.0f, 768.0f, 0.0f }, EEngineDir::Right, DoorState::close);
		AllDoor[2].push_back(NewDoor);
	}

	AllStair.resize(4);
	{
		AStair* UpStair = CreateStair({ 961.0f, 126.0f, 0.0f }, EStairType::Up, 0).get();
		AStair* DownStair = CreateStair({ 1242.0f, 414.0f, 0.0f }, EStairType::Down, 1).get();
		UpStair->SetPartnerStair(DownStair);
		DownStair->SetPartnerStair(UpStair);
	}

	{
		AStair* UpStair = CreateStair({ 576.0f, 414.0f, 0.0f }, EStairType::Up, 1).get();
		AStair* DownStair = CreateStair({ 295.0f, 702.0f, 0.0f }, EStairType::Down, 2).get();
		UpStair->SetPartnerStair(DownStair);
		DownStair->SetPartnerStair(UpStair);
	}
}

void AFactory_005::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	ExtraGangster.clear();
}

void AFactory_005::LevelReStart()
{
	Super::LevelReStart();

	TotalEnemy = 9;

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 207.0f, 127.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);

	AllEnemy.reserve(TotalEnemy);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 580.0f, 130.0f, 0.0f }, EEngineDir::Right, 3.5f, 5.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 950.0f, 130.0f, 0.0f }, EEngineDir::Left, 3.5f, 5.0f, EnemyState::patrol_stop);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1454.0f, 415.0f, 0.0f }, EEngineDir::Right, 1.8f, 5.0f, EnemyState::patrol_stop);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 247.0f, 704.0f, 0.0f }, EEngineDir::Right, 4.5f, 5.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1111.0f, 704.0f, 0.0f }, EEngineDir::Right, 5.0f, 4.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1633.0f, 704.0f, 0.0f }, EEngineDir::Left, 5.0f, 5.0f, EnemyState::patrol_stop);
	
	ExtraGangster.reserve(3);
	ExtraGangster.push_back(SpawnEnemy<AGangSter>("Gangster", { 75.0f, 127.0f, 0.0f }, EEngineDir::Right, EnemyState::none).get());
	ExtraGangster.push_back(SpawnEnemy<AGangSter>("Gangster", { 145.0f, 127.0f, 0.0f }, EEngineDir::Right, EnemyState::none).get());
	ExtraGangster.push_back(SpawnEnemy<AGangSter>("Gangster", { 215.0f, 127.0f, 0.0f }, EEngineDir::Right, EnemyState::none).get());

	AllRecComponent.reserve(10);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 657.0f, 634.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 687.0f, 634.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 754.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 784.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1713.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1743.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);
	SpawnRecComponent<ACeilLaser>("CeilLaser", { 1743.0f, 922.0f, 0.0f }, EEngineDir::Left, CeilLaserState::on);

	SpawnRecComponent<APanicSwitch>("PanicSwitch", { 1165.0f, 795.0f, 0.0f }, EEngineDir::Right, PanicSwitchState::on);
	SpawnRecComponent<AScientist>("Scientist", { 1910.0f, 703.0f, 0.0f }, EEngineDir::Left, ScientistState::idle);
	
	AllDoor.resize(3);
	{
		std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 528.0f, 192.0f, 0.0f }, EEngineDir::Right, DoorState::close);
		AllDoor[0].push_back(NewDoor);
	}

	{
		std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 1422.0f, 480.0f, 0.0f }, EEngineDir::Right, DoorState::close);
		AllDoor[1].push_back(NewDoor);
	}

	{
		std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 1070.0f, 768.0f, 0.0f }, EEngineDir::Right, DoorState::close);
		AllDoor[2].push_back(NewDoor);
	}
}

void AFactory_005::LevelReEnd()
{
	Super::LevelReEnd();

	ExtraGangster.clear();
}

void AFactory_005::ChangeStage()
{
	Super::ChangeStage();
}

void AFactory_005::ClearStart()
{
	Super::ClearStart();

	Go->SetRepeatPos({ 500.0f, 200.0f, 0.0f });
	Go->StateChange("Repeat");
}

void AFactory_005::ExtraGangsterOn()
{
	for (size_t i = 0; i < ExtraGangster.size(); i++)
	{
		ExtraGangster[i]->StateChange(EnemyState::chase_run);
	}
}

void AFactory_005::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}