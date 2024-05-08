#include "PreCompile.h"
#include "Mine.h"

AMine::AMine()
{
}

AMine::~AMine()
{
}

void AMine::BeginPlay()
{
	Super::BeginPlay();

}

void AMine::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AMine::StateInit()
{
	// State Create

	
	// State Start


	// State Update



}
