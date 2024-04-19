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
