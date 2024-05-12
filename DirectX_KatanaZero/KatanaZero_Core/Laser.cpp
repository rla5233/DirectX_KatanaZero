#include "PreCompile.h"
#include "Laser.h"

#include "PlayLevelBase.h"
#include "PlayerBase.h"
#include "MainCamera.h"

ALaser::ALaser()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Laser");
	Body->CreateAnimation(Anim::effect_laser, ImgRes::effect_laser, 0.1f, true);
	Body->SetOrder(ERenderOrder::EffectFront);
	Body->SetupAttachment(Root);
	Body->SetActive(false);

	BodyCol = CreateDefaultSubObject<UCollision>("RifleLaserCol");
	BodyCol->SetCollisionGroup(EColOrder::EnemyAttack);
	BodyCol->SetCollisionType(ECollisionType::RotRect);
	BodyCol->SetupAttachment(Body);
	BodyCol->SetActive(false);

	SetRoot(Root);
}

ALaser::~ALaser()
{
}

void ALaser::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
}

void ALaser::StateInit()
{
	// State Create
	State.CreateState(LaserState::aim);
	State.CreateState(LaserState::short_shoot);

	// State Start
	State.SetStartFunction(LaserState::aim, [=] 
		{
			LaserAlpha = 1.0f;
			Body->AnimationReset();
			Body->SetSprite(ImgRes::compo_bullet);
			Body->SetScale({ 0.0f, 2.0f, 1.0f });
			Body->SetRotationDeg({ 0.0f, 0.0f, Deg });
			Body->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
			Body->SetActive(true);
		}
	);

	State.SetStartFunction(LaserState::short_shoot, [=] 
		{
			LaserAlpha = 1.0f;
			Body->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
			Body->ChangeAnimation(Anim::effect_laser);
			Body->SetScale({ 1280.0f, 18.0f, 1.0f });
			BodyCol->SetActive(true);

			APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
			PlayLevel->GetKZMainCamera()->SetRetShakeTime(0.1f);
			PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);

			DelayCallBack(0.1f, [=] { ShortShootUpdate = true; });
		}
	);
	
	// State Update
	State.SetUpdateFunction(LaserState::aim, [=](float _DeltaTime) 
		{
			FVector CurScale = Body->GetLocalScale();
			if (1280.0f < CurScale.X)
			{
				if (0.0f < AlphaDownTimeCount)
				{
					AlphaDownTimeCount -= _DeltaTime;
					return;
				}

				LaserAlpha -= 9.0f * _DeltaTime;
				if (0.0f > LaserAlpha)
				{
					LaserAlpha = 0.0f;
					Body->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
					State.ChangeState(LaserState::short_shoot);
					return;
				}
				Body->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
				return;
			}
			else
			{
				float Rad = Deg * UEngineMath::DToR;
				float AddScaleX = 5000.0f * _DeltaTime;
				Body->AddScale({ AddScaleX, 0.0f, 0.0f });
				Body->AddPosition({ AddScaleX * 0.5f * cosf(Rad), AddScaleX * 0.5f * sinf(Rad) ,0.0f });
			}
		}
	);

	State.SetUpdateFunction(LaserState::short_shoot, [=](float _DeltaTime) 
		{
			if (false == ShortShootUpdate)
			{
				return;
			}

			float AddScaleY = -100.0f * _DeltaTime;
			Body->AddScale({ 0.0f, AddScaleY, 0.0f });

			BodyCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
				{
					APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
					FVector PlayerPos = Player->GetActorLocation();
					FVector CurPos = GetActorLocation();
					FVector AttackDir = FVector::Zero;

					if (CurPos.X < PlayerPos.X)
					{
						AttackDir = { 0.9f, 0.1f, 0.0f };
					}
					else
					{
						AttackDir = { -0.9f, 0.1f, 0.0f };
					}

					Player->HitByEnemy(AttackDir, EEnemyType::HeadHunterLaser);
				}
			);

			FVector CurScale = Body->GetLocalScale();
			if (0.0f > CurScale.Y)
			{
				Destroy();
			}
		}
	);
}

void ALaser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


