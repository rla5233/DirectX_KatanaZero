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
	GetRenderer()->CreateAnimation(Anim::player_idle_anim, ImgRes::player_idle, 0.1f, true, 0, 10);

	
}