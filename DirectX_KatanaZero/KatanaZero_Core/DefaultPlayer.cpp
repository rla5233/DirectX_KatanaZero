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

void ADefaultPlayer::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos	= { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 50.0f, 80.0f, 1.0f };
	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);
	BodyCol->SetActive(true);

	FVector FrontPos = { 0.0f, 40.0f, 0.0f };
	FVector FrontScale = { 5.0f, 80.0f, 1.0f };
	FrontCol->SetPosition(FrontPos);
	FrontCol->SetScale(FrontScale);
	FrontCol->SetActive(true);

	SetBodyInfo(BodyPos, BodyScale);
}

void ADefaultPlayer::CreateAnimation()
{
	// Player
	GetBody()->CreateAnimation(Anim::player_idle, ImgRes::player_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::player_idle_to_run, ImgRes::player_idle_to_run, 0.03f, false);
	GetBody()->CreateAnimation(Anim::player_run_to_idle, ImgRes::player_run_to_idle, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_jump, ImgRes::player_jump, 0.1f, false);
	GetBody()->CreateAnimation(Anim::player_fall, ImgRes::player_fall, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_run, ImgRes::player_run, 0.08f, true);
	GetBody()->CreateAnimation(Anim::player_postcrouch, ImgRes::player_postcrouch, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_precrouch, ImgRes::player_precrouch, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_roll, ImgRes::player_roll, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_attack, ImgRes::player_attack, 0.02f, false);
	GetBody()->CreateAnimation(Anim::player_wall_slide, ImgRes::player_wall_slide, 0.02f, false);
	GetBody()->CreateAnimation(Anim::player_flip, ImgRes::player_flip, 0.02f, false);
	GetBody()->CreateAnimation(Anim::player_kick_door, ImgRes::player_kick_door, 0.05f, false);

	GetBody()->SetFrameCallback(Anim::player_kick_door, 5, [=] { StateChange("Idle"); });
}

void ADefaultPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}