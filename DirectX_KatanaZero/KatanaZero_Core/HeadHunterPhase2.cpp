#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "PlayerBase.h"

AHeadHunterPhase2::AHeadHunterPhase2()
{
	CreateRifleLaser();
	CreateDashLaser();
	CreateDashAttack();
	CreateSparkEffect();
}

AHeadHunterPhase2::~AHeadHunterPhase2()
{
}

void AHeadHunterPhase2::BeginPlay()
{
	Super::BeginPlay();
}

void AHeadHunterPhase2::CreateRifleLaser()
{
	AllRifleLaserEffect.reserve(RifleLaserNum);
	AllRifleLaserCol.reserve(RifleLaserNum);
	for (size_t i = 0; i < RifleLaserNum; i++)
	{
		AllRifleLaserEffect.push_back(CreateDefaultSubObject<USpriteRenderer>("RifleLaserEffect"));
		AllRifleLaserEffect[i]->CreateAnimation(Anim::effect_laser, ImgRes::effect_laser, 0.1f, true);
		AllRifleLaserEffect[i]->SetOrder(ERenderOrder::EffectFront);
		AllRifleLaserEffect[i]->SetupAttachment(GetRoot());
		AllRifleLaserEffect[i]->SetActive(false);

		AllRifleLaserCol.push_back(CreateDefaultSubObject<UCollision>("RifleLaserCol"));
		AllRifleLaserCol[i]->SetCollisionGroup(EColOrder::EnemyAttack);
		AllRifleLaserCol[i]->SetCollisionType(ECollisionType::RotRect);
		AllRifleLaserCol[i]->SetupAttachment(AllRifleLaserEffect[i]);
		AllRifleLaserCol[i]->SetActive(false);
	}
}

void AHeadHunterPhase2::CreateDashLaser()
{
	DashLaser = CreateDefaultSubObject<USpriteRenderer>("DashLaser");
	DashLaser->SetSprite(ImgRes::effect_dash_laser);
	DashLaser->SetOrder(ERenderOrder::EffectBack);
	DashLaser->SetupAttachment(GetRoot());
	DashLaser->SetActive(false);
}

void AHeadHunterPhase2::CreateDashAttack()
{
	DashAttack = CreateDefaultSubObject<UCollision>("DashAttack");
	DashAttack->SetCollisionType(ECollisionType::Rect);
	DashAttack->SetCollisionGroup(EColOrder::EnemyAttack);
	DashAttack->SetScale({ 50.0f, 90.0f, 1.0f });
	DashAttack->SetPosition({ 0.0f, 45.0f, 0.0f });
	DashAttack->SetupAttachment(GetRoot());
	DashAttack->SetActive(false);
}

void AHeadHunterPhase2::CreateSparkEffect()
{
	AllSparkEffect.reserve(SparkEffectNum);
	for (int i = 0; i < SparkEffectNum; i++)
	{
		AllSparkEffect.push_back(CreateDefaultSubObject<USpriteRenderer>("SparkEffect"));
		AllSparkEffect[i]->SetOrder(ERenderOrder::EffectFront);
		AllSparkEffect[i]->SetAutoSize(1.75f, true);
		AllSparkEffect[i]->SetActive(false);

		AllSparkEffect[i]->CreateAnimation(Anim::effect_gun_spark1, ImgRes::effect_gun_spark1, 0.08f, false);
		AllSparkEffect[i]->CreateAnimation(Anim::effect_gun_spark2, ImgRes::effect_gun_spark2, 0.08f, false);
		AllSparkEffect[i]->CreateAnimation(Anim::effect_gun_spark3, ImgRes::effect_gun_spark3, 0.08f, false);
		AllSparkEffect[i]->SetFrameCallback(Anim::effect_gun_spark1, 8, [=] { AllSparkEffect[i]->SetActive(false); });
		AllSparkEffect[i]->SetFrameCallback(Anim::effect_gun_spark2, 8, [=] { AllSparkEffect[i]->SetActive(false); });
		AllSparkEffect[i]->SetFrameCallback(Anim::effect_gun_spark3, 8, [=] { AllSparkEffect[i]->SetActive(false); });
	}
}

void AHeadHunterPhase2::CreateAnimation()
{
	Super::CreateAnimation();

	Body->CreateAnimation(Anim::headhunter_shoot_gun, ImgRes::headhunter_shoot_gun, 0.08f, false);
	Body->CreateAnimation(Anim::headhunter_takeout_gun, ImgRes::headhunter_takeout_gun, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_putback_gun, ImgRes::headhunter_takeout_gun, 0.08f, false, 6, 0);
	Body->CreateAnimation(Anim::headhunter_predash, ImgRes::headhunter_predash, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_dashend, ImgRes::headhunter_dashend, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_tel_in_sweep, ImgRes::headhunter_tel_in_sweep, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_sweep, ImgRes::headhunter_sweep, 0.05f, false);

	Body->SetLastFrameCallback(Anim::headhunter_putback_gun, [=] 
		{ 
			Body->SetPosition(FVector::Zero);
			State.ChangeState(HeadHunterState::idle);
		}
	);

	Body->SetLastFrameCallback(Anim::headhunter_dashend, [=] 
		{ 
			Body->SetPosition(FVector::Zero);
			State.ChangeState(HeadHunterState::idle); 
		}
	);
}

void AHeadHunterPhase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunterPhase2::AdjustBodyPosByDir(const FVector _Pos)
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetPosition({ -_Pos.X, _Pos.Y, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ _Pos.X, _Pos.Y, 0.0f });
		break;
	}
}

void AHeadHunterPhase2::RifleLaserIdxUpdate()
{
	++RifleLaserIdx;

	if (RifleLaserNum <= RifleLaserIdx)
	{
		RifleLaserIdx = 0;
	}
}

void AHeadHunterPhase2::RifleLaserColCheck()
{
	for (size_t i = 0; i < RifleLaserNum; i++)
	{
		AllRifleLaserCol[i]->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision>(_Other))
			{
				APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
				FVector PlayerPos = Player->GetActorLocation();
				FVector CurPos = GetActorLocation();
				Player->HitByEnemy(PlayerPos - CurPos, EEnemyType::HeadHunterLaser);
			}
		);
	}
}

void AHeadHunterPhase2::SparkIdxUpdate()
{
	++SparkIdx;

	if (SparkEffectNum <= SparkIdx)
	{
		SparkIdx = 0;
	}
}
