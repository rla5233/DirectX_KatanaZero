#include "PreCompile.h"
#include "CeilLaser.h"

ACeilLaser::ACeilLaser()
{
	Laser = CreateDefaultSubObject<USpriteRenderer>("Laser");
	HitCol = CreateDefaultSubObject<UCollision>("LaserHit");
	
	Laser->SetupAttachment(GetRoot());
	HitCol->SetupAttachment(GetRoot());
}

ACeilLaser::~ACeilLaser()
{
}

void ACeilLaser::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CollisionInit();
}

void ACeilLaser::RendererInit()
{
	Laser->CreateAnimation(Anim::compo_ceil_laser_idle, ImgRes::compo_ceil_laser_idle, 0.0175f, true);
	Laser->SetOrder(ERenderOrder::EffectFront);
	Laser->SetPivot(EPivot::BOT);
	Laser->SetScale({ 4.0f, 210.0f, 1.0f });
	Laser->SetPosition({ 0.0f, -218.0f, 0.0f });

	GetBody()->SetOrder(ERenderOrder::MapComponent);
	GetBody()->SetAutoSize(2.0f, true);
}

void ACeilLaser::CollisionInit()
{
}

void ACeilLaser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACeilLaser::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState("On");


	// State Start
	State.SetStartFunction("On", [=] 
		{ 
			GetBody()->SetSprite(ImgRes::compo_ceil_laser_on); 
			Laser->ChangeAnimation(Anim::compo_ceil_laser_idle);
		}
	);
	
	// State Update
	State.SetUpdateFunction("On", [=](float _DeltaTime) {});


	// State End


}


