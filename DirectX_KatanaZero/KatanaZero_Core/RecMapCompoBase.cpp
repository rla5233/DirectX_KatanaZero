#include "PreCompile.h"
#include "RecMapCompoBase.h"

ARecMapCompoBase::ARecMapCompoBase()
{
}

ARecMapCompoBase::~ARecMapCompoBase()
{
}

void ARecMapCompoBase::BeginPlay()
{
	Super::BeginPlay();

	URecordingObject::SetActor(this);

	StateInit();
}

void ARecMapCompoBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ARecMapCompoBase::StateInit()
{
	// State Create
	State.CreateState("Replay");

	// State Start
	State.SetStartFunction("Replay", [=] { SetReplayStart(); });

	// State Update
	State.SetUpdateFunction("Replay", [=](float _DeltaTime) { Replaying(_DeltaTime); });

	// State End

}
