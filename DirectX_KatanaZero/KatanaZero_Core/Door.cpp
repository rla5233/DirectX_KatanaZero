#include "PreCompile.h"
#include "Door.h"

ADoor::ADoor()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("DoorBody");
	BodyCol = CreateDefaultSubObject<UCollision>("DoorBody");
	HitCol = CreateDefaultSubObject<UCollision>("DoorHit");
	
	Body->SetupAttachment(Root);
	BodyCol->SetupAttachment(Root);
	HitCol->SetupAttachment(Root);

	SetRoot(Root);
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
	State.SetStartFunction("Idle", [=] { Body->ChangeAnimation(Anim::compo_door_idle); });

	// State Update

	
	// State End
}

void ADoor::RendererInit()
{
	Body->CreateAnimation(Anim::compo_door_idle, ImgRes::compo_door, 0.1f, 0, false);
	Body->CreateAnimation(Anim::compo_door_open, ImgRes::compo_door, 0.05f, false);
	Body->SetOrder(ERenderOrder::MapComponent);
	Body->SetAutoSize(2.0f, true);
}

void ADoor::CollisionInit()
{
}
