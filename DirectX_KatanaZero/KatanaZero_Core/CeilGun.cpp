#include "PreCompile.h"
#include "CeilGun.h"

#include "PlayerBase.h"

ACeilGun::ACeilGun()
{
	Laser = CreateDefaultSubObject<USpriteRenderer>("Laser");
	Smoke = CreateDefaultSubObject<USpriteRenderer>("Smoke");
	Spark = CreateDefaultSubObject<USpriteRenderer>("Spark");
	HitCol = CreateDefaultSubObject<UCollision>("LaserHit");

	Laser->SetupAttachment(GetRoot());
	Smoke->SetupAttachment(GetRoot());
	Spark->SetupAttachment(GetRoot());
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
	Laser->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	Spark->CreateAnimation(Anim::effect_gun_spark1, ImgRes::effect_gun_spark1, 0.06f, false);
	Spark->CreateAnimation(Anim::effect_gun_spark2, ImgRes::effect_gun_spark2, 0.06f, false);
	Spark->CreateAnimation(Anim::effect_gun_spark3, ImgRes::effect_gun_spark3, 0.06f, false);
	Spark->SetFrameCallback(Anim::effect_gun_spark1, 8, [=] { Spark->SetActive(false); });
	Spark->SetFrameCallback(Anim::effect_gun_spark2, 8, [=] { Spark->SetActive(false); });
	Spark->SetFrameCallback(Anim::effect_gun_spark3, 8, [=] { Spark->SetActive(false); });
	Spark->SetOrder(ERenderOrder::EffectFront);
	Spark->AddRotationDeg({ 0.0f, 0.0f, -90.0f });
	Spark->SetPosition({ 5.0f, -54.0f, 0.0f });
	Spark->SetAutoSize(2.0f, true);
	Spark->SetActive(false);

	
	Smoke->CreateAnimation(Anim::effect_gun_smoke1, ImgRes::effect_gun_smoke1, 0.04f, false);
	Smoke->CreateAnimation(Anim::effect_gun_smoke3, ImgRes::effect_gun_smoke3, 0.04f, false);
	Smoke->SetFrameCallback(Anim::effect_gun_smoke1, 10, [=] { Smoke->SetActive(false); });
	Smoke->SetFrameCallback(Anim::effect_gun_smoke3, 11, [=] { Smoke->SetActive(false); });
	Smoke->SetOrder(ERenderOrder::EffectFront);
	Smoke->AddRotationDeg({ 0.0f, 0.0f, -90.0f });
	Smoke->SetAutoSize(2.0f, true);
	Smoke->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	Smoke->SetActive(false);

	GetBody()->SetSprite(ImgRes::compo_ceil_gun);
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
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
	State.CreateState(CeilGunState::on);
	State.CreateState(CeilGunState::off);
	State.CreateState(CeilGunState::shoot);

	// State Start
	State.SetStartFunction(CeilGunState::on, [=]
		{
			Laser->SetActive(true);
			Laser->ChangeAnimation(Anim::compo_ceilgun_col_idle);

			HitCol->SetActive(true);
		}
	);

	State.SetStartFunction(CeilGunState::off, [=]
		{
			HitCol->SetActive(false);
			Laser->SetActive(false);
		}
	);

	State.SetStartFunction(CeilGunState::shoot, [=]
		{
			Laser->SetActive(false);
			SetRandomSparkAnim();
			SetRandomSmokeAnim();

			DelayCallBack(0.4f, [=] { State.ChangeState(CeilGunState::on); });
		}
	);

	// State Update
	State.SetUpdateFunction(CeilGunState::off, [=](float _DeltaTime) {});
	State.SetUpdateFunction(CeilGunState::on, [=](float _DeltaTime)
		{			
			HitCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
				{
					APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
					Player->HitByEnemy(EEnemyType::CeilGun);
					State.ChangeState(CeilGunState::shoot);
					return;
				}
			);


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

	State.SetUpdateFunction(CeilGunState::shoot, [=](float _DeltaTime)
		{
		}
	);
}

void ACeilGun::SetRandomSparkAnim()
{
	Spark->SetActive(true);
	Spark->AnimationReset();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);

	switch (RandomValue)
	{
	case 1:
		Spark->ChangeAnimation(Anim::effect_gun_spark1);
		break;
	case 2:
		Spark->ChangeAnimation(Anim::effect_gun_spark2);
		break;
	case 3:
		Spark->ChangeAnimation(Anim::effect_gun_spark3);
		break;
	}
}

void ACeilGun::SetRandomSmokeAnim()
{
	Smoke->SetActive(true);
	Smoke->AnimationReset();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);

	switch (RandomValue)
	{
	case 1:
		Smoke->SetPosition({ 5.0f, -54.0f, 0.0f });
		Smoke->ChangeAnimation(Anim::effect_gun_smoke1);
		break;
	case 2:
		Smoke->SetPosition({ 5.0f, -54.0f, 0.0f });
		Smoke->ChangeAnimation(Anim::effect_gun_smoke3);
		break;
	}
}