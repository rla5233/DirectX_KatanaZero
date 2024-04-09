#include "PreCompile.h"
#include "DefaultPlayer.h"

ADefaultPlayer::ADefaultPlayer()
{
}

ADefaultPlayer::~ADefaultPlayer()
{
}

void ADefaultPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();

	StateChange("Idle");
}

void ADefaultPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ADefaultPlayer::CreateAnimation()
{
	GetRenderer()->CreateAnimation(Anim::player_idle, ImgRes::player_idle, 0.1f, true, 0, 10);
	GetRenderer()->CreateAnimation(Anim::player_idle_to_run, ImgRes::player_idle_to_run, 0.1f, true, 0, 10);
	GetRenderer()->CreateAnimation(Anim::player_run_to_idle, ImgRes::player_run_to_idle, 0.1f, true, 0, 10);

	
}