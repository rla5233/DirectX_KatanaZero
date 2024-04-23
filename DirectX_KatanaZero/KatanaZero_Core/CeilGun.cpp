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

	RendererInit();
	CollisionInit();
}

void ACeilGun::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACeilGun::RendererInit()
{
	Laser->CreateAnimation(Anim::compo_ceil_laser_idle, ImgRes::compo_ceil_laser_idle, 0.0175f, true);
	Laser->CreateAnimation(Anim::compo_ceil_laser_attack, ImgRes::compo_ceil_laser_attack, 0.06f, false);
	Laser->SetFrameCallback(Anim::compo_ceil_laser_attack, 3, [=] { State.ChangeState("On"); });

	Laser->SetOrder(ERenderOrder::EffectFront);
	Laser->SetPivot(EPivot::BOT);
	Laser->SetScale({ 4.0f, 210.0f, 1.0f });
	Laser->SetPosition({ 0.0f, -218.0f, 0.0f });

	GetBody()->SetOrder(ERenderOrder::MapComponent);
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
	State.CreateState("Off");

	// State Start
	State.SetStartFunction("Off", [=] 
		{
			HitCol->SetActive(false);
			Laser->SetActive(false);
		}
	);

	// State Update
	State.SetUpdateFunction("Off", [=](float _DeltaTime) {});
}