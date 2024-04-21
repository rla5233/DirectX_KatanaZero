#include "PreCompile.h"
#include "RecMapCompoBase.h"

ARecMapCompoBase::ARecMapCompoBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Body");
	Body->SetupAttachment(Root);

	SetRoot(Root);
}

ARecMapCompoBase::~ARecMapCompoBase()
{
}

void ARecMapCompoBase::BeginPlay()
{
	Super::BeginPlay();

	URecordingObject::SetActor(this);

	StateInit();

	SetRecordingSize();
}

void ARecMapCompoBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	DefaultUpdate(_DeltaTime);
}

void ARecMapCompoBase::DefaultUpdate(float _DeltaTime)
{
	std::string CurState = State.GetCurStateName();

	if ("Replay" != CurState)
	{
		Recording(_DeltaTime);
	}
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
