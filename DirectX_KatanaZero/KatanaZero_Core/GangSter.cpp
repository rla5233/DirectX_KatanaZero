#include "PreCompile.h"
#include "GangSter.h"

#include "PlayLevelBase.h"
#include "UpMark.h"

AGangSter::AGangSter()
{
}

AGangSter::~AGangSter()
{
}

void AGangSter::BeginPlay()
{
	Super::BeginPlay();

	CollisionInit();
	CreateAnimation();
}

void AGangSter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AGangSter::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos = { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 50.0f, 80.0f, 1.0f };

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);

	SetBodyInfo(BodyPos, BodyScale);
}

void AGangSter::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::enemy_gangster_idle, ImgRes::enemy_gangster_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_run, ImgRes::enemy_gangster_run, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_turn, ImgRes::enemy_gangster_turn, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_hitfall, ImgRes::enemy_gangster_hitfall, 0.06f, false);
	GetBody()->CreateAnimation(Anim::enemy_gangster_dead, ImgRes::enemy_gangster_dead, 0.06f, false);

	GetBody()->SetFrameCallback(Anim::enemy_gangster_turn, 6, [=]
		{
			GetBody()->AddPosition({ 0.0f, -2.0f, 0.0f });
		}
	);
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

	GetBody()->ChangeAnimation(Anim::enemy_gangster_idle);
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
	
	GetBody()->AnimationReset();
	GetBody()->AddPosition({ 0.0f, 2.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_gangster_idle);

	DelayCallBack(1.0f, [=] 
		{
			GetBody()->AddPosition({ 0.0f, -2.0f, 0.0f });
			StateChange(EnemyState::chase_run);
		}
	);
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
		Result = true;
	}

	return Result;
}

void AGangSter::ChaseMarkUpdate()
{
	ChaseMark->SetActorLocation(GetActorLocation() + FVector(0.0f, 105.0f, 0.0f));
}
