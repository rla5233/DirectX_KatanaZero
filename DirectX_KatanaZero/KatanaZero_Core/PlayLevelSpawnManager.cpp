#include "PreCompile.h"
#include "PlayLevelSpawnManager.h"

#include "PlayLevelBase.h"
#include "Stair.h"

UPlayLevelSpawnManager::UPlayLevelSpawnManager()
{
}

UPlayLevelSpawnManager::~UPlayLevelSpawnManager()
{
}

std::shared_ptr<AStair> UPlayLevelSpawnManager::CreateStair(const FVector& _Pos, EStairType _StairType, int _FloorNum)
{
	std::shared_ptr<AStair> NewStair = GameMode->GetWorld()->SpawnActor<AStair>("Stair");
	NewStair->SetActorLocation(_Pos);
	NewStair->SetStairType(_StairType);
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllStair[_FloorNum].push_back(NewStair);
	return NewStair;
}

void UPlayLevelSpawnManager::PushEnemy(std::shared_ptr<AEnemyBase> _Enemy)
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllEnemy.push_back(_Enemy);
}

void UPlayLevelSpawnManager::PushRecComponent(std::shared_ptr<ARecMapCompoBase> _Component)
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllRecComponent.push_back(_Component);
}