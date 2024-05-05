#include "PreCompile.h"
#include "BossLevelBase.h"

#include "ColMapObject.h"
#include "MainCamera.h"
#include "FailedMsg.h"
#include "MouseAim.h"

#include "DiamondTransition.h"
#include "WaveEffect.h"

ABossLevelBase::ABossLevelBase()
{
}

ABossLevelBase::~ABossLevelBase()
{
}

void ABossLevelBase::BeginPlay()
{
	Super::BeginPlay();

	StateInit();

	WaveEffect = GetWorld()->GetLastTarget()->AddEffect<UWaveEffect>();
	DiaTransition = GetWorld()->SpawnActor<ADiamondTransition>("DiaTransition");

	Aim = GetWorld()->SpawnActor<AMouseAim>("MouseAim");

	FailedMsg = GetWorld()->SpawnActor<AFailedMsg>("FailedMsg");
}

void ABossLevelBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	MainCamera = GetWorld()->SpawnActor<AMainCamera>("ContentsMainCamera");
	ColMap = GetWorld()->SpawnActor<AColMapObject>("ColMap");

	WaveEffect->Active(false);
}

void ABossLevelBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ABossLevelBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
