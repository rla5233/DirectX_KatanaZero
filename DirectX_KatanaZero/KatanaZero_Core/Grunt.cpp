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

void AGrunt::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos = { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 50.0f, 60.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);
}

void AGrunt::IdleStart()
{
	Super::IdleStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::HitFallStart()
{
	Super::HitFallStart();

	GetBody()->ChangeAnimation(Anim::enemy_grunt_hitfall);
}

void AGrunt::DeadStart()
{
	Super::DeadStart();

	GetBody()->AddPosition({ 0.0f, 13.0f, 0.0f });
	GetBody()->ChangeAnimation(Anim::enemy_grunt_dead);
}

void AGrunt::PatrolWalkStart()
{
	Super::PatrolWalkStart();

	SetVelocityByDir({ 100.0f, 0.0f, 0.0f });
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

void AGrunt::RunStart()
{
	Super::RunStart();
	
	SetVelocity({ 350.0f, 0.0f, 0.0f });

	GetBody()->ChangeAnimation(Anim::enemy_grunt_run);
}

void AGrunt::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::enemy_grunt_idle, ImgRes::enemy_grunt_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::enemy_grunt_walk, ImgRes::enemy_grunt_walk, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_grunt_run, ImgRes::enemy_grunt_run, 0.07f, true);
	GetBody()->CreateAnimation(Anim::enemy_grunt_turn, ImgRes::enemy_grunt_turn, 0.08f, false);
	GetBody()->CreateAnimation(Anim::enemy_grunt_hitfall, ImgRes::enemy_grunt_hitfall, 0.08f, false);
	GetBody()->CreateAnimation(Anim::enemy_grunt_dead, ImgRes::enemy_grunt_dead, 0.08f, false);
}