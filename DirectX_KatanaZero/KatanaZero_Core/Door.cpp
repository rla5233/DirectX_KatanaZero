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
	CollisionInit();
}

void ADoor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


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
	BodyCol->SetCollisionType(ECollisionType::Rect);
	BodyCol->SetCollisionGroup(EColOrder::Door);
	BodyCol->SetScale({ 25.0f, 120.0f, 1.0f });
	BodyCol->SetPosition({ 37.0f, 0.0f, 0.0f });

	BodyCol->SetActive(true);
	HitCol->SetActive(false);
}

void ADoor::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState("Idle");
	State.CreateState("Open");

	// State Start
	State.SetStartFunction("Idle", [=] 
		{ 
			EEngineDir Dir = GetBody()->GetDir();
			FVector BodyColPos = BodyCol->GetLocalPosition();
			switch (Dir)
			{
			case EEngineDir::Left:
				
				break;
			case EEngineDir::Right:
				BodyColPos.X = -BodyColPos.X;
				break;
			}

			BodyCol->SetPosition(BodyColPos);
			GetBody()->ChangeAnimation(Anim::compo_door_idle); 
		}
	);

	// State Update


	// State End
}
