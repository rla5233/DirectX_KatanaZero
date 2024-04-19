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
	FVector BodyScale = { 50.0f, 80.0f, 0.0f };

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);

	SetBodyInfo(BodyPos, BodyScale);
}

void AGangSter::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::enemy_gangster_idle, ImgRes::enemy_gangster_idle, 0.1f, true);
}

void AGangSter::IdleStart()
{
	GetBody()->ChangeAnimation(Anim::enemy_gangster_idle);
}
