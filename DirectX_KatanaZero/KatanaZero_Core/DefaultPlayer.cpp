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
	GetRenderer()->CreateAnimation(Anim::player_idle, ImgRes::player_idle, 0.1f, true);
	GetRenderer()->CreateAnimation(Anim::player_idle_to_run, ImgRes::player_idle_to_run, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_run_to_idle, ImgRes::player_run_to_idle, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_jump, ImgRes::player_jump, 0.1f, false);
	GetRenderer()->CreateAnimation(Anim::player_fall, ImgRes::player_fall, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_run, ImgRes::player_run, 0.08f, true);
	GetRenderer()->CreateAnimation(Anim::player_postcrouch, ImgRes::player_postcrouch, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_precrouch, ImgRes::player_precrouch, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_roll, ImgRes::player_roll, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_attack, ImgRes::player_attack, 0.06f, false);
}
