#include "PreCompile.h"
#include "GangSter.h"

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
	FVector BodyScale = { 50.0f, 60.0f, 1.0f };

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);

	SetBodyInfo(BodyPos, BodyScale);
}

void AGangSter::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::enemy_gangster_idle, ImgRes::enemy_gangster_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::enemy_gangster_hitfall, ImgRes::enemy_gangster_hitfall, 0.06f, false);
	GetBody()->CreateAnimation(Anim::enemy_gangster_dead, ImgRes::enemy_gangster_dead, 0.06f, false);
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

	GetBody()->ChangeAnimation(Anim::enemy_gangster_dead);
}