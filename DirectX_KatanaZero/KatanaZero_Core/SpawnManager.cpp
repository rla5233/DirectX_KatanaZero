#include "PreCompile.h"
#include "SpawnManager.h"

#include "PlayLevelBase.h"
#include "BoundaryColObject.h"

USpawnManager::USpawnManager()
{
}

USpawnManager::~USpawnManager()
{
}

void USpawnManager::CreateBoundaryCol(const FVector& _Pos, const FVector& _Scale)
{
	std::shared_ptr<ABoundaryColObject> Boundary = GameMode->GetWorld()->SpawnActor<ABoundaryColObject>("Boundary");
	Boundary->SetActorLocation(_Pos);
	Boundary->SetActorScale3D(_Scale);
	
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GameMode);
	PlayLevel->AllBoundaryCol.push_back(Boundary);
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
