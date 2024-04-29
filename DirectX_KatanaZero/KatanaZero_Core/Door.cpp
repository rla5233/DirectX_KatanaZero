#include "PreCompile.h"
#include "Door.h"

#include "EnemyBase.h"

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
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(2.0f, true);
}

void ADoor::CollisionInit()
{
	BodyCol->SetCollisionType(ECollisionType::Rect);
	BodyCol->SetCollisionGroup(EColOrder::Door);
	BodyCol->SetScale({ 25.0f, 80.0f, 1.0f });
	BodyCol->SetPosition({ 37.0f, 0.0f, 0.0f });

	HitCol->SetCollisionType(ECollisionType::Rect);
	HitCol->SetCollisionGroup(EColOrder::PlayerAttack);
	HitCol->SetScale({ 100.0f, 120.0f, 1.0f });

	BodyCol->SetActive(true);
	HitCol->SetActive(false);
}

void ADoor::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(DoorState::close);
	State.CreateState(DoorState::open);
	State.CreateState(DoorState::opened);

	// State Start
	State.SetStartFunction(DoorState::close, [=]
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

	State.SetStartFunction(DoorState::open, [=]
		{
			BodyCol->SetActive(false);
			HitCol->SetActive(true);
			GetBody()->ChangeAnimation(Anim::compo_door_open);
			DelayCallBack(0.25f, [=] { State.ChangeState(DoorState::opened); });
		}
	);

	State.SetStartFunction(DoorState::opened, [=] {});

	// State Update
	State.SetUpdateFunction(DoorState::close, [=](float _DeltaTime) {});
	State.SetUpdateFunction(DoorState::open, [=](float _DeltaTime)
		{
			HitCol->CollisionEnter(EColOrder::Enemy, [=](std::shared_ptr<UCollision> _Other)
				{
					AEnemyBase* Enemy = dynamic_cast<AEnemyBase*>(_Other->GetActor());
					Enemy->HitByDoor(GetBody()->GetDir());
					State.ChangeState(DoorState::opened);
					return;
				}
			);
		}
	);

	State.SetUpdateFunction(DoorState::opened, [=](float _DeltaTime) {});


	// State End
	State.SetEndFunction(DoorState::open, [=] { HitCol->SetActive(false); });
}
