#include "PreCompile.h"
#include "Door.h"

ADoor::ADoor()
{
	BodyCol = CreateDefaultSubObject<UCollision>("DoorBody");
	HitCol = CreateDefaultSubObject<UCollision>("DoorHit");
	
	BodyCol->SetupAttachment(GetRoot());
	HitCol->SetupAttachment(GetRoot());
}

ADoor::~ADoor()
{
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
}

void ADoor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void ADoor::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState("Idle");
	State.CreateState("Open");

	// State Start
	State.SetStartFunction("Idle", [=] { GetBody()->ChangeAnimation(Anim::compo_door_idle); });

	// State Update

	
	// State End
}

void ADoor::RendererInit()
{
	GetBody()->CreateAnimation(Anim::compo_door_idle, ImgRes::compo_door, 0.1f, false, 0, 0);
	GetBody()->CreateAnimation(Anim::compo_door_open, ImgRes::compo_door, 0.05f, false);
	GetBody()->SetOrder(ERenderOrder::MapComponent);
	GetBody()->SetAutoSize(2.0f, true);
}

void ADoor::CollisionInit()
{
}
