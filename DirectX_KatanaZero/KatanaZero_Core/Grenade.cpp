#include "PreCompile.h"
#include "Grenade.h"

#include "PlayerBase.h"

AGrenade::AGrenade()
{
	Circle = CreateDefaultSubObject<USpriteRenderer>("Circle");
	Circle->SetOrder(ERenderOrder::EffectBack);
	Circle->SetupAttachment(GetRoot());
	Circle->SetSprite(ImgRes::compo_yellow_circle);
	Circle->SetSamplering(ETextureSampling::LINEARCLAMP);
	Circle->SetActive(false);

	BodyCol = CreateDefaultSubObject<UCollision>("Grenade_Col");
	BodyCol->SetCollisionGroup(EColOrder::EnemyAttack);
	BodyCol->SetCollisionType(ECollisionType::CirCle);
	BodyCol->SetScale({	300.0f, 300.0f, 1.0f });
	BodyCol->SetupAttachment(GetRoot());
	BodyCol->SetActive(false);

	Explosion.reserve(ExplosionNum);
	for (size_t i = 0; i < ExplosionNum; i++)
	{
		Explosion.push_back(CreateDefaultSubObject<USpriteRenderer>("Explosion"));
		Explosion[i]->SetOrder(ERenderOrder::EffectFront);
		Explosion[i]->SetupAttachment(GetRoot());
		Explosion[i]->SetAutoSize(2.5f, true);
		Explosion[i]->SetActive(false);

		Explosion[i]->CreateAnimation(Anim::effect_explosion, ImgRes::effect_explosion, 0.06f, true);
		Explosion[i]->SetLastFrameCallback(Anim::effect_explosion, [=] 
			{ 
				BodyCol->SetActive(false);
				Explosion[i]->SetActive(false);
			}
		);		
	}
}

AGrenade::~AGrenade()
{
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);
	FVector BodyPos = { 0.0f, 0.0f, 0.0f };
	FVector BodyScale = { 14.0f, 18.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	GetBody()->SetSprite(ImgRes::compo_grenade);
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(1.0f, true);
	GetBody()->SetActive(false);

	State.ChangeState(GrenadeState::none);
}

void AGrenade::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(GrenadeState::none);
	State.CreateState(GrenadeState::shoot);
	State.CreateState(GrenadeState::explosion);

	// State Start
	State.SetStartFunction(GrenadeState::none, [=] {});
	State.SetStartFunction(GrenadeState::shoot, [=] 
		{
			Velocity = ShootDir;
			Velocity *= ShootSpeed;

			if (0.0f < Velocity.X)
			{
				GetBody()->SetDir(EEngineDir::Right);
			}
			else
			{
				GetBody()->SetDir(EEngineDir::Left);
			}

			GetBody()->SetActive(true);
			ShootTimeCount = 1.0f;
		}
	);

	State.SetStartFunction(GrenadeState::explosion, [=] 
		{
			Velocity = FVector::Zero;
			CircleScale = 0.0f;
			Circle->SetActive(true);
			ExplosionOrder = 0;
		}
	);

	// State Update
	State.SetUpdateFunction(GrenadeState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(GrenadeState::shoot, [=](float _DeltaTime) 
		{
			if (0.0f > ShootTimeCount)
			{
				State.ChangeState(GrenadeState::explosion);
				return;
			}

			EEngineDir Dir = GetBody()->GetDir();

			// 속도 업데이트
			ApplyGravity(_DeltaTime);

			if (true == IsColWall(Dir))
			{
				switch (Dir)
				{
				case EEngineDir::Left:
					AddActorLocation({ 10.0f, 0.0f, 0.0f });
					break;
				case EEngineDir::Right:
					AddActorLocation({ -10.0f, 0.0f, 0.0f });
					break;
				}

				Velocity.X *= -0.2f;
			}

			if (true == IsOnGround(Dir))
			{
				Velocity = FVector::Zero;
			}

			// 위치 업데이트
			PosUpdate(_DeltaTime);

			ShootTimeCount -= _DeltaTime;
		}
	);

	State.SetUpdateFunction(GrenadeState::explosion, [=](float _DeltaTime) 
		{
			switch (ExplosionOrder)
			{
			case 0:
				ExplosionUpdate(_DeltaTime);
				break;
			case 1:
				ExplosionUpdate1(_DeltaTime);
				break;
			case 2:
				ExplosionUpdate2(_DeltaTime);
				break;
			default:
				break;
			}
		}
	);
}

void AGrenade::ExplosionUpdate(float _DeltaTime)
{
	CircleScale += 1500.0f * _DeltaTime;

	if (280.0f < CircleScale)
	{
		CircleScale = 280.0f;
		CircleAlpha = 1.0f;
		ExplosionOrder = 1;
	}

	Circle->SetScale({ CircleScale, CircleScale, 0.0f });
}

void AGrenade::ExplosionUpdate1(float _DeltaTime)
{
	CircleAlpha -= 2.0f * _DeltaTime;

	if (0.0f > CircleAlpha)
	{
		CircleAlpha = 1.0f;

		for (size_t i = 0; i < Explosion.size(); i++)
		{
			Explosion[i]->ChangeAnimation(Anim::effect_explosion);

			float Deg = UEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
			Deg *= UEngineMath::DToR;
			FVector Pos = { cosf(Deg), sinf(Deg), 0.0f };

			float PosScale = 0.0f;
			if (i < 10)
			{
				PosScale = UEngineRandom::MainRandom.RandomFloat(20.0f, 60.0f);
			}
			else
			{
				PosScale = UEngineRandom::MainRandom.RandomFloat(60.0f, 140.0f);
			}

			Explosion[i]->SetPosition({ PosScale * Pos.X, PosScale * Pos.Y, 0.0f });
			Explosion[i]->SetActive(true);
		}

		BodyCol->SetActive(true);
		GetBody()->SetActive(false);
		Circle->SetActive(false);
		ExplosionOrder = 2;
	}

	Circle->SetMulColor({ 1.0f, 1.0f, 1.0f, CircleAlpha });
}

void AGrenade::ExplosionUpdate2(float _DeltaTime)
{
	BodyCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			FVector Dir = Player->GetActorLocation() - GetActorLocation();
			Player->HitByEnemy(Dir, EEnemyType::HeadHunterLaser);
		}
	);
}

void AGrenade::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}