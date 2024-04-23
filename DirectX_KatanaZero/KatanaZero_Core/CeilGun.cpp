#include "PreCompile.h"
#include "CeilGun.h"

ACeilGun::ACeilGun()
{
	Laser = CreateDefaultSubObject<USpriteRenderer>("Laser");
	HitCol = CreateDefaultSubObject<UCollision>("LaserHit");

	Laser->SetupAttachment(GetRoot());
	HitCol->SetupAttachment(GetRoot());
}

ACeilGun::~ACeilGun()
{
}

void ACeilGun::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);

	RendererInit();
	CollisionInit();
}

void ACeilGun::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACeilGun::RendererInit()
{
	Laser->CreateAnimation(Anim::compo_ceilgun_col_idle, ImgRes::compo_ceilgun_col_idle, 0.0175f, true);

	Laser->SetOrder(ERenderOrder::EffectFront);
	Laser->SetPivot(EPivot::BOT);
	Laser->SetScale({ 4.0f, 204.0f, 1.0f });
	Laser->SetPosition({ 0.0f, -218.0f, 0.0f });
	Laser->SetPlusColor({ -0.2f, 0.1f, 0.1f });

	GetBody()->SetSprite(ImgRes::compo_ceil_gun);
	GetBody()->SetOrder(ERenderOrder::MapComponent);
	GetBody()->SetPosition({ 0.0f, -3.0f, 0.0f });
	GetBody()->SetAutoSize(2.0f, true);
}

void ACeilGun::CollisionInit()
{
	HitCol->SetCollisionType(ECollisionType::Rect);
	HitCol->SetCollisionGroup(EColOrder::EnemyAttack);
	HitCol->SetScale({ 4.0f, 210.0f, 1.0f });
	HitCol->SetPosition({ 0.0f, -113.0f, 0.0f });
}

void ACeilGun::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState("On");
	State.CreateState("Off");

	// State Start
	State.SetStartFunction("On", [=] 
		{
			Laser->ChangeAnimation(Anim::compo_ceilgun_col_idle);

			HitCol->SetActive(true);
			Laser->SetActive(true);
		}
	);

	State.SetStartFunction("Off", [=] 
		{
			HitCol->SetActive(false);
			Laser->SetActive(false);
		}
	);

	// State Update
	State.SetUpdateFunction("On", [=](float _DeltaTime) 
		{
			if (LeftPoint_X > GetActorLocation().X)
			{
				GetBody()->SetDir(EEngineDir::Right);
				Velocity.X *= -1.0f;
			}

			if (RightPoint_X < GetActorLocation().X)
			{
				GetBody()->SetDir(EEngineDir::Left);
				Velocity.X *= -1.0f;
			}

			// 위치 업데이트
			PosUpdate(_DeltaTime);
		}
	);

	State.SetUpdateFunction("Off", [=](float _DeltaTime) {});
}