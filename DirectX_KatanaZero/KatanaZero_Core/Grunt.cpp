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

	StateChange("Run");
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

void AGrunt::Idle(float _DeltaTime)
{
	Super::Idle(_DeltaTime);

}

void AGrunt::WalkStart()
{
	Super::WalkStart();

	SetVelocityByDir({ 100.0f, 0.0f, 0.0f });

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_walk);
}

void AGrunt::Walk(float _DeltaTime)
{
	Super::Walk(_DeltaTime);
}

void AGrunt::RunStart()
{
	Super::RunStart();
	
	SetVelocity({ 200.0f, 0.0f, 0.0f });

	GetRenderer()->ChangeAnimation(Anim::enemy_grunt_run);
}

void AGrunt::Run(float _DeltaTime)
{
	Super::Run(_DeltaTime);

}

void AGrunt::CreateAnimation()
{
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_idle, ImgRes::enemy_grunt_idle, 0.1f, true);
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_walk, ImgRes::enemy_grunt_walk, 0.07f, true);
	GetRenderer()->CreateAnimation(Anim::enemy_grunt_run, ImgRes::enemy_grunt_run, 0.07f, true);
}