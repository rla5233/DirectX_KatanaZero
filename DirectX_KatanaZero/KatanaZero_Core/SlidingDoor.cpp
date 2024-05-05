#include "PreCompile.h"
#include "SlidingDoor.h"

ASlidingDoor::ASlidingDoor()
{
	DoorLED = CreateDefaultSubObject<USpriteRenderer>("SlidingDoor_LED");
	DoorLED->SetupAttachment(GetRoot());
}

ASlidingDoor::~ASlidingDoor()
{
}

void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CreateAnimation();
}

void ASlidingDoor::RendererInit()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(2.0f, true);
}

void ASlidingDoor::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::compo_sliding_door_close, ImgRes::compo_sliding_door_close, 0.1f, false);
}

void ASlidingDoor::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(SlidingDoorState::close);

	// State Start
	State.SetStartFunction(SlidingDoorState::close, [=] 
		{
			GetBody()->ChangeAnimation(Anim::compo_sliding_door_close);
		}
	);

	// State Update
	State.SetUpdateFunction(SlidingDoorState::close, [=](float _DeltaTime) {});

}

void ASlidingDoor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
