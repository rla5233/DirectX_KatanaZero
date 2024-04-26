#include "PreCompile.h"
#include "CeilLaser.h"

#include "PlayerBase.h"

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
	Laser->CreateAnimation(Anim::compo_ceil_laser_attack, ImgRes::compo_ceil_laser_attack, 0.06f, false);
	Laser->SetFrameCallback(Anim::compo_ceil_laser_attack, 3, [=] { State.ChangeState(CeilLaserState::on); });

	Laser->SetOrder(ERenderOrder::EffectFront);
	Laser->SetPivot(EPivot::BOT);
	Laser->SetScale({ 4.0f, 210.0f, 1.0f });
	Laser->SetPosition({ 0.0f, -218.0f, 0.0f });

	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(2.0f, true);
}

void ACeilLaser::CollisionInit()
{
	HitCol->SetCollisionType(ECollisionType::Rect);
	HitCol->SetCollisionGroup(EColOrder::EnemyAttack);
	HitCol->SetScale({ 4.0f, 210.0f, 1.0f });
	HitCol->SetPosition({ 0.0f, -113.0f, 0.0f });
}

void ACeilLaser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACeilLaser::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(CeilLaserState::on);
	State.CreateState(CeilLaserState::shoot);
	State.CreateState(CeilLaserState::off);

	// State Start
	State.SetStartFunction(CeilLaserState::on, [=] 
		{ 
			GetBody()->SetSprite(ImgRes::compo_ceil_laser_on); 
			Laser->ChangeAnimation(Anim::compo_ceil_laser_idle);
			Laser->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });
			Laser->SetScale({ 4.0f, 210.0f, 1.0f });
			Laser->SetActive(true);
			HitCol->SetActive(true);
		}
	);

	State.SetStartFunction(CeilLaserState::shoot, [=]
		{	
			Laser->SetScale({ 10.0f, 210.0f, 1.0f });
			Laser->SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
			Laser->ChangeAnimation(Anim::compo_ceil_laser_attack); 
		}
	);

	State.SetStartFunction(CeilLaserState::off, [=]
		{
			GetBody()->SetSprite(ImgRes::compo_ceil_laser_off);
			Laser->SetActive(false);
			HitCol->SetActive(false);
		}
	);
	
	// State Update
	State.SetUpdateFunction(CeilLaserState::on, [=](float _DeltaTime)
		{
			HitCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
				{
					APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
					Player->HitByEnemy();
					State.ChangeState(CeilLaserState::shoot);
					return;
				}
			);
		}
	);

	State.SetUpdateFunction(CeilLaserState::shoot, [=](float _DeltaTime)
		{ 
			Laser->AddScale({ -40.0f * _DeltaTime, 0.0f, 0.0f }); 
		}
	);

	State.SetUpdateFunction(CeilLaserState::off, [=](float _DeltaTime) {});

	// State End


}


