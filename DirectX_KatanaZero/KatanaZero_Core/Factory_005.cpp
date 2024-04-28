#include "PreCompile.h"
#include "Factory_005.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"
#include "Grunt.h"
#include "GangSter.h"
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
	TotalEnemy = 3;
	FloorY = { 414.0f, 702.0f };

	MainCamera->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap5, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background5, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ -5.0f, 127.0f, 0.0f });

	AllEnemy.reserve(TotalEnemy);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 580.0f, 130.0f, 0.0f }, EEngineDir::Right, 3.5f, 5.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 950.0f, 130.0f, 0.0f }, EEngineDir::Left, 3.5f, 5.0f, EnemyState::patrol_stop);

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
}

void AFactory_005::LevelReStart()
{
	Super::LevelReStart();

	TotalEnemy = 3;

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 207.0f, 127.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);

	AllEnemy.reserve(TotalEnemy);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 580.0f, 130.0f, 0.0f }, EEngineDir::Right, 3.5f, 5.0f, EnemyState::patrol_walk);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 950.0f, 130.0f, 0.0f }, EEngineDir::Left, 3.5f, 5.0f, EnemyState::patrol_stop);

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

void AFactory_005::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}