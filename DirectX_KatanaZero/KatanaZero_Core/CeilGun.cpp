#include "PreCompile.h"
#include "CeilGun.h"

ACeilGun::ACeilGun()
{
	Laser = CreateDefaultSubObject<USpriteRenderer>("Laser");
	Spark = CreateDefaultSubObject<USpriteRenderer>("Spark");
	Smoke = CreateDefaultSubObject<USpriteRenderer>("Smoke");
	HitCol = CreateDefaultSubObject<UCollision>("LaserHit");

	Laser->SetupAttachment(GetRoot());
	Spark->SetupAttachment(GetRoot());
	Smoke->SetupAttachment(GetRoot());
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

	Spark->CreateAnimation(Anim::effect_gun_spark1, ImgRes::effect_gun_spark1, 0.06f, false);
	Spark->CreateAnimation(Anim::effect_gun_spark2, ImgRes::effect_gun_spark2, 0.06f, false);
	Spark->CreateAnimation(Anim::effect_gun_spark3, ImgRes::effect_gun_spark3, 0.06f, false);
	Spark->SetFrameCallback(Anim::effect_gun_spark1, 8, [=] { Spark->SetActive(false); State.ChangeState("On"); });
	Spark->SetFrameCallback(Anim::effect_gun_spark2, 8, [=] { Spark->SetActive(false); State.ChangeState("On"); });
	Spark->SetFrameCallback(Anim::effect_gun_spark3, 8, [=] { Spark->SetActive(false); State.ChangeState("On"); });
	Spark->SetOrder(ERenderOrder::EffectFront);
	Spark->AddRotationDeg({ 0.0f, 0.0f, -90.0f });
	Spark->SetPosition({ 5.0f, -54.0f, 0.0f });
	Spark->SetAutoSize(2.0f, true);

	
	Smoke->SetActive(false);

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
	State.CreateState("Shoot");

	// State Start
	State.SetStartFunction("On", [=] 
		{
			Laser->SetActive(true);
			Laser->ChangeAnimation(Anim::compo_ceilgun_col_idle);

			HitCol->SetActive(true);
		}
	);

	State.SetStartFunction("Off", [=] 
		{
			HitCol->SetActive(false);
			Laser->SetActive(false);
		}
	);

	State.SetStartFunction("Shoot", [=] 
		{
			Laser->SetActive(false);

			SetRandomSparkAnim();

		}
	);

	// State Update
	State.SetUpdateFunction("Off", [=](float _DeltaTime) {});
	State.SetUpdateFunction("On", [=](float _DeltaTime) 
		{			
			HitCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
				{
					State.ChangeState("Shoot");
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

	State.SetUpdateFunction("Shoot", [=](float _DeltaTime) 
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