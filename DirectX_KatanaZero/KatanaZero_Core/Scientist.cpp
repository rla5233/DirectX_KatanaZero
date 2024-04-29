#include "PreCompile.h"
#include "Scientist.h"

AScientist::AScientist()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	
	SetRoot(Root);
}

AScientist::~AScientist()
{
}

void AScientist::BeginPlay()
{
	Super::BeginPlay();

}

void AScientist::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AScientist::StateInit()
{
	Super::StateInit();

}

void AScientist::RendererInit()
{
}

void AScientist::CollisionInit()
{
}

void AScientist::CreateAnimation()
{
}
