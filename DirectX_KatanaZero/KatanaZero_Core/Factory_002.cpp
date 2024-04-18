#include "PreCompile.h"
#include "Factory_002.h"

#include "ColMapObject.h"
#include "DefaultPlayer.h"
#include "Grunt.h"
#include "Up_HUD.h"

AFactory_002::AFactory_002()
{
}

AFactory_002::~AFactory_002()
{
}

void AFactory_002::BeginPlay()
{
	Super::BeginPlay();
}

void AFactory_002::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GetWorld()->GetMainCamera()->SetActorLocation({ 665.0f, 392.0f, -100.0f });

	ColMap->SetColMapSprite(ImgRes::factory_colmap2, 1.0f, true);
	ColMap->SetBGSprite(ImgRes::factory_background2, 1.0f, true);

	Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });

	AllEnemy.reserve(3);

	std::shared_ptr<AGrunt> NewGrunt = GetWorld()->SpawnActor<AGrunt>("Grunt");
	NewGrunt->SetActorLocation({ 1075.0f, 400.0f, 0.0f });
	NewGrunt->SetRendererDir(EEngineDir::Left);
	NewGrunt->SetPatrolTime(3.5f, 5.0f);
	NewGrunt->StateChange("PatrolWalk");

	NewGrunt = GetWorld()->SpawnActor<AGrunt>("Grunt");
	NewGrunt->SetActorLocation({ 340.0f, 400.0f, 0.0f });
	NewGrunt->SetRendererDir(EEngineDir::Right);
	NewGrunt->StateChange("Idle");

	AllEnemy.push_back(NewGrunt);
}

void AFactory_002::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AFactory_002::ChangeStage()
{
	GEngine->ChangeLevel("Factory_003");
}

void AFactory_002::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AFactory_002::ResetPlayer()
{
	if (UEngineInput::IsDown('R'))
	{
		Player->SetActorLocation({ 175.0f, 147.0f, 0.0f });
	}
}
