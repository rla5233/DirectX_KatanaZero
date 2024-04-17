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

	StateChange("Idle");
}

void AGrunt::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AGrunt::CreateAnimation()
{
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_idle, ImgRes::enemy_grunt_idle, 0.02f, true);
}

void AGrunt::IdleStart()
{
	Super::IdleStart();

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_idle);
}

void AGrunt::Idle(float _DeltaTime)
{
	Super::Idle(_DeltaTime);

}
