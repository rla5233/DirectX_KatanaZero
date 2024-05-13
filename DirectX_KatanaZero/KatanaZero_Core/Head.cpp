#include "PreCompile.h"
#include "Head.h"

AHead::AHead()
{
}

AHead::~AHead()
{
}

void AHead::BeginPlay()
{
	Super::BeginPlay();

	StateInit();

}

void AHead::StateInit()
{
	// State Create


	// State Start


	// State Update


}

void AHead::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


