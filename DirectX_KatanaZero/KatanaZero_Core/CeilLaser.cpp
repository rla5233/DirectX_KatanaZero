#include "PreCompile.h"
#include "CeilLaser.h"

ACeilLaser::ACeilLaser()
{
	HitCol = CreateDefaultSubObject<UCollision>("LaserHit");
	HitCol->SetupAttachment(GetRoot());
}

ACeilLaser::~ACeilLaser()
{
}

void ACeilLaser::BeginPlay()
{
	Super::BeginPlay();
}

void ACeilLaser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACeilLaser::StateInit()
{
	Super::StateInit();

	// State Create


	// State Start

	
	// State Update


	// State End


}
