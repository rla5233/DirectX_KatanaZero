#include "PreCompile.h"
#include "GangSter.h"

#include "PlayLevelBase.h"
#include "PlayerBase.h"
#include "UpMark.h"

AGangSter::AGangSter()
{
	Spark = CreateDefaultSubObject<USpriteRenderer>("Gangster_Attack_Effect");
	Spark->SetupAttachment(GetRoot());

	Bullet.Renderer = CreateDefaultSubObject<USpriteRenderer>("Gangster_Bullet");
	Bullet.Collision = CreateDefaultSubObject<UCollision>("Gangster_Bullet");
	Bullet.Collision->SetupAttachment(Bullet.Renderer);
}

AGangSter::~AGangSter()
{
}

void AGangSter::BeginPlay()
{
	Super::BeginPlay();

	CollisionInit();

	Spark->SetActive(false);
	Spark->SetAutoSize(2.0f, true);
	Spark->SetOrder(ERenderOrder::EffectFront);

	Bullet.Renderer->SetActive(false);
	Bullet.Renderer->SetAutoSize(1.0f, true);
	Bullet.Renderer->SetOrder(ERenderOrder::EffectFront);
	Bullet.Renderer->SetSprite(ImgRes::compo_bullet);

	CreateAnimation();
}

void AGangSter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BulletUpdate(_DeltaTime);
}

void AGangSter::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos = { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 50.0f, 80.0f, 1.0f };

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);

	SetBodyInfo(BodyPos, BodyScale);

	Bullet.Collision->SetCollisionGroup(EColOrder::EnemyAttack);
	Bullet.Collision->SetCollisionType(ECollisionType::RotRect);
	Bullet.Collision->SetScale({ 2.0f, 2.0f, 1.0f });
}

void AGangSter::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::enemy_gangster_idle, ImgRes::enemy_gangster_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_run, ImgRes::enemy_gangster_run, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_turn, ImgRes::enemy_gangster_turn, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_hitfall, ImgRes::enemy_gangster_hitfall, 0.06f, false);
	GetBody()->CreateAnimation(Anim::enemy_gangster_dead, ImgRes::enemy_gangster_dead, 0.06f, false);

	GetBody()->SetFrameCallback(Anim::enemy_gangster_turn, 6,	[=] { GetBody()->AddPosition({ 0.0f, -2.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::enemy_gangster_dead, 11,	[=] { UEngineSound::SoundPlay(SoundRes::enemy_chest_ground).SetVolume(0.5f); });

	Spark->CreateAnimation(Anim::effect_gun_spark1, ImgRes::effect_gun_spark1, 0.06f, false);
	Spark->CreateAnimation(Anim::effect_gun_spark2, ImgRes::effect_gun_spark2, 0.06f, false);
	Spark->CreateAnimation(Anim::effect_gun_spark3, ImgRes::effect_gun_spark3, 0.06f, false);
	Spark->SetFrameCallback(Anim::effect_gun_spark1, 8, [=] { Spark->SetActive(false); });
	Spark->SetFrameCallback(Anim::effect_gun_spark2, 8, [=] { Spark->SetActive(false); });
	Spark->SetFrameCallback(Anim::effect_gun_spark3, 8, [=] { Spark->SetActive(false); });
}

void AGangSter::IdleStart()
{
	Super::IdleStart();

	GetBody()->ChangeAnimation(Anim::enemy_gangster_idle);
}

void AGangSter::HitFallStart()
{
	Super::HitFallStart();

	GetBody()->ChangeAnimation(Anim::enemy_gangster_hitfall);
}

void AGangSter::DeadStart()
{
	Super::DeadStart();

	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_dead);
}

void AGangSter::ChaseRunStart()
{
	Super::ChaseRunStart();

	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_run);
}

void AGangSter::ChaseRunEnd()
{
	Super::ChaseRunEnd();
	
	GetBody()->AddPosition({ 0.0f, -2.0f, 0.0f });
}

void AGangSter::ChaseStopStart()
{
	Super::ChaseStopStart();

	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_idle);
}

void AGangSter::ChaseStopEnd()
{
	Super::ChaseStopEnd();

	GetBody()->AddPosition({ 0.0f, -2.0f, 0.0f });
}

void AGangSter::ChaseTurnStart()
{
	Super::ChaseTurnStart();

	DirChange();
	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_turn);
}

void AGangSter::ChaseStairUpStart()
{
	Super::ChaseStairUpStart();

	GetBody()->ChangeAnimation(Anim::enemy_gangster_run);
}

void AGangSter::ChaseStairDownStart()
{
	Super::ChaseStairDownStart();

	GetBody()->ChangeAnimation(Anim::enemy_gangster_run);
}

void AGangSter::ChaseStairTurnStart()
{
	Super::ChaseStairTurnStart();

	DirChange();
	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_turn);
}

void AGangSter::ChaseAttackStart()
{
	Super::ChaseAttackStart();
	
	CanAttack = false;
	AttackDelayTimeCount = Const::enmey_gangster_attack_delay;

	GetBody()->AnimationReset();
	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_idle);

	SetAttackEffect();
	SetBullet();

	DelayCallBack(1.0f, [=] 
		{
			GetBody()->AddPosition({ 0.0f, -2.0f, 0.0f });
			if (EnemyState::chase_attack == GetCurState())
			{
				StateChange(EnemyState::chase_run);
			}
		}
	);

	USoundManager::SoundPlay_GunFire();
}

void AGangSter::ChaseAttack(float _DeltaTime)
{
	Super::ChaseAttack(_DeltaTime);
}

bool AGangSter::AttackRangeCheck()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	int PlayerFloorNum = PlayLevel->GetPlayerFloorNum();

	FVector DiffVec = PlayerPos - GetActorLocation();
	float DiffLen = UContentsMath::GetVectorNorm(DiffVec);

	if (AttackRange >= DiffLen && PlayerFloorNum == FloorNum)
	{
		AttackDir = DiffVec.Normalize2DReturn();
		Result = true;
	}

	return Result;
}

void AGangSter::ChaseMarkUpdate()
{
	ChaseMark->SetActorLocation(GetActorLocation() + FVector(0.0f, 105.0f, 0.0f));
}

void AGangSter::SetAttackEffect()
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

	EEngineDir Dir = GetBody()->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Spark->SetDir(EEngineDir::Left);
		Spark->SetPosition({ -90.0f, 51.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Spark->SetDir(EEngineDir::Right);
		Spark->SetPosition({ 90.0f, 51.0f, 0.0f });
		break;
	}
}

void AGangSter::SetBullet()
{
	Bullet.IsReflect = false;
	Bullet.Renderer->SetActive(true);
	Bullet.Collision->SetActive(true);
	Bullet.Velocity = AttackDir * 1750.0f;

	FVector GangSterPos = GetActorLocation();
	EEngineDir Dir = GetBody()->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Bullet.Renderer->SetPosition(GangSterPos + FVector(-70.0f, 45.0f, 0.0f));
		break;
	case EEngineDir::Right:
		Bullet.Renderer->SetPosition(GangSterPos + FVector(70.0f, 45.0f, 0.0f));
		break;
	}

	float Deg = UContentsMath::GetAngleToAxisX2D(AttackDir);
	Bullet.Renderer->SetRotationDeg({ 0.0f, 0.0f, Deg });
}

void AGangSter::BulletUpdate(float _DeltaTime)
{
	if (false == Bullet.Renderer->IsActive())
	{
		return;
	}

	Bullet.Renderer->AddPosition(Bullet.Velocity * _DeltaTime);

	Bullet.Collision->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			Player->HitByEnemy(Bullet.Velocity);
			Bullet.Renderer->SetActive(false);
			Bullet.Collision->SetActive(false);
		}
	);

	Bullet.Collision->CollisionEnter(EColOrder::PlayerAttack, [=](std::shared_ptr<UCollision> _Other)
		{
			Bullet.Velocity *= -1.0f;
			Bullet.IsReflect = true;
			UEngineSound::SoundPlay(SoundRes::player_parrying).SetVolume(1.0f);
		}
	);

	Bullet.Collision->CollisionEnter(EColOrder::Enemy, [=](std::shared_ptr<UCollision> _Other)
		{
			if (true == Bullet.IsReflect)
			{
				AEnemyBase* Enemy = dynamic_cast<AEnemyBase*>(_Other->GetActor());
				Enemy->HitByPlayer(Bullet.Velocity.Normalize2DReturn());
				Bullet.Renderer->SetActive(false);
				Bullet.Collision->SetActive(false);
			}
		}
	);
}