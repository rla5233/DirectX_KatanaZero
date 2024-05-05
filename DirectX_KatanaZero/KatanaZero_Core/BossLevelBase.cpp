#include "PreCompile.h"
#include "BossLevelBase.h"

ABossLevelBase::ABossLevelBase()
{
}

ABossLevelBase::~ABossLevelBase()
{
}

void ABossLevelBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABossLevelBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABossLevelBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}

void ABossLevelBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

