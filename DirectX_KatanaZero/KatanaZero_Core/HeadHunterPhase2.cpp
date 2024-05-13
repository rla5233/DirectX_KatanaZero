#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
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
	RifleLaserEffect = CreateDefaultSubObject<USpriteRenderer>("RifleLaserEffect");
	RifleLaserEffect->CreateAnimation(Anim::effect_laser, ImgRes::effect_laser, 0.1f, true);
	RifleLaserEffect->SetOrder(ERenderOrder::EffectFront);
	RifleLaserEffect->SetupAttachment(GetRoot());
	RifleLaserEffect->SetActive(false);

	RifleLaserCol = CreateDefaultSubObject<UCollision>("RifleLaserCol");
	RifleLaserCol->SetCollisionGroup(EColOrder::EnemyAttack);
	RifleLaserCol->SetCollisionType(ECollisionType::RotRect);
	RifleLaserCol->SetupAttachment(RifleLaserEffect);
	RifleLaserCol->SetActive(false);
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
	Body->CreateAnimation(Anim::headhunter_tel_out_sweep, ImgRes::headhunter_tel_out_sweep, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_sweep, ImgRes::headhunter_sweep, 0.05f, false);
	Body->CreateAnimation(Anim::headhunter_tel_in, ImgRes::headhunter_tel_in, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_tel_out, ImgRes::headhunter_tel_in, 0.06f, false, 3, 0);
	Body->CreateAnimation(Anim::headhunter_tel_ground, ImgRes::headhunter_tel_ground, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_tel_in_wall, ImgRes::headhunter_tel_in_wall, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_reveal_bomb, ImgRes::headhunter_reveal_bomb, 0.08f, false);
	Body->CreateAnimation(Anim::headhunter_bomb_run, ImgRes::headhunter_bomb_run, 0.06f, true);
	Body->CreateAnimation(Anim::headhunter_diefly_stop, ImgRes::headhunter_diefly, 0.06f, false, 0, 0);
	Body->CreateAnimation(Anim::headhunter_diefly, ImgRes::headhunter_diefly, 0.1f, true);
	Body->CreateAnimation(Anim::headhunter_dieland, ImgRes::headhunter_dieland, 0.1f, false);
	Body->CreateAnimation(Anim::headhunter_dead, ImgRes::headhunter_dead, 0.25f, true);
	Body->CreateAnimation(Anim::headhunter_dead_nohead, ImgRes::headhunter_dead_nohead, 0.1f, false);

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
	
	Body->SetFrameCallback(Anim::headhunter_tel_ground, 3, [=]
		{
			AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
			FVector CurPos = GetActorLocation();
			CurPos.X -= 40.0f;
			CurPos.Y += 40.0f;
			PlayLevel->CreateLaser(CurPos, 180.0f, 0.2f);
		}
	);

	Body->SetFrameCallback(Anim::headhunter_reveal_bomb, 5, [=]
		{
			UEngineSound::SoundPlay(SoundRes::hh_bombed_arm);
		}
	);

	Body->SetFrameCallback(Anim::headhunter_dieland, 0, [=]
		{
			UEngineSound::SoundPlay(SoundRes::hh_floor_hit);
		}
	);
}

void AHeadHunterPhase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


// Sub State
void AHeadHunterPhase2::RestartStart()
{
	Super::RestartStart();

	for (size_t i = 0; i < AllSparkEffect.size(); i++)
	{
		AllSparkEffect[i]->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	}

	DashLaser->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
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

void AHeadHunterPhase2::RifleLaserColCheck()
{
	RifleLaserCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision>(_Other))
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			FVector PlayerPos = Player->GetActorLocation();
			FVector CurPos = GetActorLocation();
			Player->HitByEnemy(PlayerPos - CurPos, EEnemyType::HeadHunterLaser);
		}
	);
}

void AHeadHunterPhase2::SparkIdxUpdate()
{
	++SparkIdx;

	if (SparkEffectNum <= SparkIdx)
	{
		SparkIdx = 0;
	}
}
