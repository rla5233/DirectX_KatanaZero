#include "PreCompile.h"
#include "Factory_002.h"

#include "MainCamera.h"
#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Up_HUD.h"
#include "Grunt.h"
#include "GangSter.h"
#include "Stair.h"
#include "Door.h"
#include "Go.h"

#include "FactoryIntroUI.h"

AFactory_002::AFactory_002()
{
}

AFactory_002::~AFactory_002()
{
}

void AFactory_002::BeginPlay()
{
	Super::BeginPlay();

	IntroUI = GetWorld()->SpawnActor<AFactoryIntroUI>("IntroUI");
}

void AFactory_002::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 60.0f;
	TotalEnemy = 3;
	FloorY = { 397.0f };

	ColMap->SetColMapSprite(ImgRes::factory_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background2, 1.0f, true);

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ -20.0f, 111.0f, 0.0f });
	Player->DirChange(EEngineDir::Right);
	Player->SetIntroType(EIntroType::FactoryBegin);

	MainCamera->SetPlayer(Player.get());
	MainCamera->SetMapTex(ColMap->GetMapTex().get());
	MainCamera->StateChange(MainCameraState::chaseplayer);

	AllEnemy.reserve(TotalEnemy);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1075.0f, 400.0f, 0.0f }, EEngineDir::Left, 3.5f, 5.0f, EnemyState::patrol_walk);
	SpawnEnemy<AGrunt>("Grunt", { 340.0f, 400.0f, 0.0f }, EEngineDir::Right, EnemyState::idle);
	SpawnEnemy<AGangSter>("GangSter", { 540.0f, 400.0f, 0.0f }, EEngineDir::Left, EnemyState::idle);

	AllRecComponent.reserve(1);
	AllDoor.resize(2);
	std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 560.0f, 464.0f, 0.0f }, EEngineDir::Left, DoorState::close);
	AllDoor[1].push_back(NewDoor);

	AllStair.resize(2);
	AStair* UpStair = CreateStair({ 768.0f, 110.0f, 0.0f }, EStairType::Up, 0).get();
	AStair* DownStair = CreateStair({ 1057.0f, 398.0f, 0.0f }, EStairType::Down, 1).get();
	UpStair->SetPartnerStair(DownStair);
	DownStair->SetPartnerStair(UpStair);

	State.ChangeState(PlayLevelState::transition_off);

	DelayCallBack(5.5f, [=]
		{
			IntroUI->StateChange(FactoryIntroUIState::intro);
		}
	);
}

void AFactory_002::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	IntroUI->Off();
}

void AFactory_002::LevelReStart()
{
	Super::LevelReStart();

	TotalEnemy = 3;

	Player = GetWorld()->SpawnActor<ADefaultPlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ 192.0f, 111.0f, 0.0f });
	Player->SubStateChange(PlayerSubState::play);
	Player->StateChange(PlayerState::idle);
	Player->DirChange(EEngineDir::Right);
	MainCamera->SetPlayer(Player.get());

	AllEnemy.reserve(TotalEnemy);
	SpawnPatrolEnemy<AGrunt>("Grunt", { 1075.0f, 400.0f, 0.0f }, EEngineDir::Left, 3.5f, 5.0f, EnemyState::patrol_walk);
	SpawnEnemy<AGrunt>("Grunt", { 340.0f, 400.0f, 0.0f }, EEngineDir::Right, EnemyState::idle);
	SpawnEnemy<AGangSter>("GangSter", { 540.0f, 400.0f, 0.0f }, EEngineDir::Left, EnemyState::idle);

	AllRecComponent.reserve(1);
	AllDoor.resize(2);
	std::shared_ptr<ADoor> NewDoor = SpawnRecComponent<ADoor>("Door", { 560.0f, 464.0f, 0.0f }, EEngineDir::Left, DoorState::close);
	AllDoor[1].push_back(NewDoor);
}

void AFactory_002::ChangeStage()
{
	Super::ChangeStage();

	GEngine->ChangeLevel("Factory_003");
}

void AFactory_002::ClearStart()
{
	Super::ClearStart();

	Go->SetRepeatPos({ 500.0f, 200.0f, 0.0f });
	Go->StateChange("Repeat");
}

void AFactory_002::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
