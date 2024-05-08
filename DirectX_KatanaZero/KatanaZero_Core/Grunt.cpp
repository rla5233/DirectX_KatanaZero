#include "PreCompile.h"
#include "Grunt.h"

#include "PlayLevelBase.h"
#include "PlayerBase.h"

AGrunt::AGrunt()
{
	AttackEffect = CreateDefaultSubObject<USpriteRenderer>("Grunt_Attack_Effect");
	AttackCol = CreateDefaultSubObject<UCollision>("Grunt_Attack_Col");

	AttackEffect->SetupAttachment(GetRoot());
	AttackCol->SetupAttachment(GetRoot());
}

AGrunt::~AGrunt()
{
}

void AGrunt::BeginPlay()
{
	Super::BeginPlay();

	EffectInit();
	CreateAnimation();
}

void AGrunt::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	{
		std::string Msg = std::format("Grunt_State : {}\n", GetCurState());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Grunt_Floor : {}\n", FloorNum);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void AGrunt::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos = { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 50.0f, 80.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);

	AttackCol->SetCollisionType(ECollisionType::RotRect);
	AttackCol->SetCollisionGroup(EColOrder::EnemyAttack);
	AttackCol->SetScale({ 40.0f, 70.0f, 1.0f });
	AttackCol->SetActive(false);
}

void AGrunt::EffectInit()
{
	AttackEffect->SetPivot(EPivot::BOT);
	AttackEffect->SetOrder(ERenderOrder::EffectFront);
	AttackEffect->SetAutoSize(2.0f, true);
	AttackEffect->SetActive(false);
}

void AGrunt::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::enemy_grunt_idle, ImgRes::enemy_grunt_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::enemy_grunt_walk, ImgRes::enemy_grunt_walk, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_grunt_run, ImgRes::enemy_grunt_run, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_grunt_turn, ImgRes::enemy_grunt_turn, 0.08f, false);
	GetBody()->CreateAnimation(Anim::enemy_grunt_hitfall, ImgRes::enemy_grunt_hitfall, 0.08f, false);
	GetBody()->CreateAnimation(Anim::enemy_grunt_dead, ImgRes::enemy_grunt_dead, 0.08f, false);
	GetBody()->CreateAnimation(Anim::enemy_grunt_attack, ImgRes::enemy_grunt_attack, 0.07f, false);
	
	GetBody()->SetFrameCallback(Anim::enemy_grunt_turn, 8,		[=] { DirChange(); });
	GetBody()->SetFrameCallback(Anim::enemy_grunt_attack, 2,	[=] { SetAttackEffect(AttackDeg); });
	GetBody()->SetFrameCallback(Anim::enemy_grunt_attack, 4,	[=] { SetAttackCollision(AttackDir, AttackDeg); });
	GetBody()->SetFrameCallback(Anim::enemy_grunt_dead, 13,		[=] { UEngineSound::SoundPlay(SoundRes::enemy_chest_ground).SetVolume(0.5f); });

	AttackEffect->CreateAnimation(Anim::effect_grunt_attack, ImgRes::effect_grunt_attack, 0.08f, false);
	AttackEffect->SetLastFrameCallback(Anim::effect_grunt_attack, [=] 
		{ 
			AttackEffect->SetActive(false);
			AttackCol->SetActive(false);
		}
	);
}

// FSM
void AGrunt::IdleStart()
{
	Super::IdleStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::HitFallStart()
{
	Super::HitFallStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_hitfall);
	GetBody()->AddPosition({ 0.0f, -10.0f, 0.0f });
}

void AGrunt::DeadStart()
{
	Super::DeadStart();

	GetBody()->AddPosition({ 0.0f, 11.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_grunt_dead);
}

void AGrunt::PatrolWalkStart()
{
	Super::PatrolWalkStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_walk);
}

void AGrunt::PatrolTurnStart()
{
	Super::PatrolTurnStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_turn);
}

void AGrunt::PatrolStopStart()
{
	Super::PatrolStopStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::ChaseRunStart()
{
	Super::ChaseRunStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_run);
}

void AGrunt::ChaseStopStart()
{
	Super::ChaseRunStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::ChaseTurnStart()
{
	Super::ChaseTurnStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_turn);
}

void AGrunt::ChaseStairUpStart()
{
	Super::ChaseStairUpStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_run);
}

void AGrunt::ChaseStairDownStart()
{
	Super::ChaseStairDownStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_run);
}

void AGrunt::ChaseStairTurnStart()
{
	Super::ChaseStairTurnStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_turn);
}

void AGrunt::ChaseAttackStart()
{
	Super::ChaseAttackStart();

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	AttackDir = PlayerPos - GetActorLocation();
	AttackDir.Normalize2D();
	AttackDeg = UContentsMath::GetAngleToX_2D(AttackDir);

	GetBody()->AnimationReset();
	GetBody()->ChangeAnimation(Anim::enemy_grunt_attack);
	UEngineSound::SoundPlay(SoundRes::enemy_punch).SetVolume(0.75f);
}

void AGrunt::ChaseAttack(float _DeltaTime)
{
	Super::ChaseAttack(_DeltaTime);

	// Collison Check
	AttackCol->CollisionStay(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			Player->HitByEnemy(AttackDir);
		}
	);

	if (true == Body->IsCurAnimationEnd())
	{
		StateChange(EnemyState::chase_run);
		return;
	}
}

bool AGrunt::AttackRangeCheck()
{
	bool Result = false;
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();

	FVector DiffVec = PlayerPos - GetActorLocation();
	float DiffLen = UContentsMath::GetVectorNorm(DiffVec);
	
	if (AttackRange >= DiffLen)
	{
		Result = true;
	}

	return Result;
}

// Setting 
void AGrunt::SetAttackEffect(float _Deg)
{
	AttackEffect->SetActive(true);
	AttackEffect->AnimationReset();
	AttackEffect->ChangeAnimation(Anim::effect_grunt_attack);

	EEngineDir Dir = GetBody()->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		AttackEffect->SetRotationDeg({ 180.0f, 0.0f, _Deg });
		break;
	case EEngineDir::Right:
		AttackEffect->SetRotationDeg({ 0.0f, 0.0f, _Deg });
		break;
	}
}

void AGrunt::SetAttackCollision(const FVector& _Dir, float _Deg)
{
	AttackCol->SetPosition(_Dir * 50.0f);
	AttackCol->AddPosition({ 0.0f, 40.0f, 0.0f });
	AttackCol->SetRotationDeg({ 0.0f, 0.0f, _Deg });
	AttackCol->SetActive(true);
}

