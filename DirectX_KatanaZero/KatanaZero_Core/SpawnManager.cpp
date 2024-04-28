#include "PreCompile.h"
#include "SpawnManager.h"

#include "PlayLevelBase.h"
#include "Stair.h"

USpawnManager::USpawnManager()
{
}

USpawnManager::~USpawnManager()
{
}

std::shared_ptr<AStair> USpawnManager::CreateStair(const FVector& _Pos, EStairType _StairType, int _FloorNum)
{
	std::shared_ptr<AStair> NewStair = GameMode->GetWorld()->SpawnActor<AStair>("Stair");
	NewStair->SetActorLocation(_Pos);
	NewStair->SetStairType(_StairType);
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllStair[_FloorNum].push_back(NewStair);
	return NewStair;
}

void USpawnManager::PushEnemy(std::shared_ptr<AEnemyBase> _Enemy)
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllEnemy.push_back(_Enemy);
}

void USpawnManager::PushRecComponent(std::shared_ptr<ARecMapCompoBase> _Component)
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllRecComponent.push_back(_Component);
}