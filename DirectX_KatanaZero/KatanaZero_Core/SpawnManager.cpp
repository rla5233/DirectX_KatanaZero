#include "PreCompile.h"
#include "SpawnManager.h"

#include "PlayLevelBase.h"

USpawnManager::USpawnManager()
{
}

USpawnManager::~USpawnManager()
{
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