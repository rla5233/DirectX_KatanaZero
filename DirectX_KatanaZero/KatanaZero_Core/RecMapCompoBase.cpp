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
	SetRecordingSize();
	StateInit();
}

void ARecMapCompoBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	DefaultUpdate(_DeltaTime);
}

void ARecMapCompoBase::DefaultUpdate(float _DeltaTime)
{
	if (true == IsRecording())
	{
		Recording(_DeltaTime);
	}
}

void ARecMapCompoBase::StateInit()
{
	// State Create
	State.CreateState(RecCompoState::replay);

	// State Start
	State.SetStartFunction(RecCompoState::replay, [=] { SetReplayStart(); });

	// State Update
	State.SetUpdateFunction(RecCompoState::replay, [=](float _DeltaTime) { Replaying(_DeltaTime); });

	// State End

}
