#include "PreCompile.h"
#include "EndingLevel.h"

AEndingLevel::AEndingLevel()
{
}

AEndingLevel::~AEndingLevel()
{
}

void AEndingLevel::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void AEndingLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AEndingLevel::StateInit()
{
	// State Create
	State.CreateState(EndingLevelState::fade_in);

	// State Start
	State.SetStartFunction(EndingLevelState::fade_in, [=] 
		{

		}
	);

	// State Update
	State.SetUpdateFunction(EndingLevelState::fade_in, [=](float _DeltaTime) 
		{

		}
	);

}
