#include "PreCompile.h"
#include "Grunt.h"

AGrunt::AGrunt()
{
}

AGrunt::~AGrunt()
{
}

void AGrunt::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
}

void AGrunt::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AGrunt::IdleStart()
{
	Super::IdleStart();

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::HitFallStart()
{
	Super::HitFallStart();

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_hitfall);
}

void AGrunt::PatrolWalkStart()
{
	Super::PatrolWalkStart();

	SetTimeCount(PatrolWalkTime);
	SetVelocityByDir({ 100.0f, 0.0f, 0.0f });
	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_walk);
}

void AGrunt::PatrolTurnStart()
{
	Super::PatrolTurnStart();

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_turn);
}

void AGrunt::PatrolStopStart()
{
	Super::PatrolStopStart();

	SetTimeCount(PatrolStopTime);
	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::RunStart()
{
	Super::RunStart();
	
	SetVelocity({ 350.0f, 0.0f, 0.0f });

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_run);
}

void AGrunt::Run(float _DeltaTime)
{
	Super::Run(_DeltaTime);

}

void AGrunt::TurnStart()
{
	Super::TurnStart();

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_turn);
}

void AGrunt::Turn(float _DeltaTime)
{
	Super::Turn(_DeltaTime);
}

void AGrunt::CreateAnimation()
{
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_idle, ImgRes::enemy_grunt_idle, 0.1f, true);
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_walk, ImgRes::enemy_grunt_walk, 0.07f, true);
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_run, ImgRes::enemy_grunt_run, 0.07f, true);
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_turn, ImgRes::enemy_grunt_turn, 0.08f, false);
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_hitfall, ImgRes::enemy_grunt_hitfall, 0.08f, false);
}