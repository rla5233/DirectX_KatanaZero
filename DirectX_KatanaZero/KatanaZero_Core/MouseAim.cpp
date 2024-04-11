#include "PreCompile.h"
#include "MouseAim.h"

AMouseAim::AMouseAim()
{
	Aim = CreateDefaultSubObject<USpriteRenderer>("MouseAim");
}

AMouseAim::~AMouseAim()
{
}

void AMouseAim::BeginPlay()
{
	Super::BeginPlay();


}

void AMouseAim::StateInit()
{


}

void AMouseAim::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


