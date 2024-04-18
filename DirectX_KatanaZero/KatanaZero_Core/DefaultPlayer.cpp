#include "PreCompile.h"
#include "DefaultPlayer.h"

ADefaultPlayer::ADefaultPlayer()
{
	Effect = CreateDefaultSubObject<USpriteRenderer>("Player_Effect");

	Effect->SetupAttachment(GetRoot());
}

ADefaultPlayer::~ADefaultPlayer()
{
}

void ADefaultPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	Effect->SetOrder(ERenderOrder::Effect);
	Effect->SetActive(false);

	StateChange("Idle");
}

void ADefaultPlayer::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos	= { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 50.0f, 80.0f, 0.0f };

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);

	SetBodyInfo(BodyPos, BodyScale);
}

void ADefaultPlayer::SetAttackEffect(float _Deg)
{
	APlayerBase::SetAttackEffect(_Deg);
	
	Effect->ChangeAnimation(Anim::effect_player_slash);
	Effect->SetAutoSize(2.0f, true);
	Effect->SetPosition({ 0.0f, 30.0f, 0.0f });
	Effect->SetRotationDeg({ 0.0f, 0.0f, _Deg });
	Effect->SetActive(true);
}

void ADefaultPlayer::CreateAnimation()
{
	// Player
	GetRenderer()->CreateAnimation(Anim::player_idle, ImgRes::player_idle, 0.1f, true);
	GetRenderer()->CreateAnimation(Anim::player_idle_to_run, ImgRes::player_idle_to_run, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_run_to_idle, ImgRes::player_run_to_idle, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_jump, ImgRes::player_jump, 0.1f, false);
	GetRenderer()->CreateAnimation(Anim::player_fall, ImgRes::player_fall, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_run, ImgRes::player_run, 0.08f, true);
	GetRenderer()->CreateAnimation(Anim::player_postcrouch, ImgRes::player_postcrouch, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_precrouch, ImgRes::player_precrouch, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_roll, ImgRes::player_roll, 0.06f, false);
	GetRenderer()->CreateAnimation(Anim::player_attack, ImgRes::player_attack, 0.02f, false);
	GetRenderer()->CreateAnimation(Anim::player_wall_slide, ImgRes::player_wall_slide, 0.02f, false);
	GetRenderer()->CreateAnimation(Anim::player_flip, ImgRes::player_flip, 0.02f, false);

	// Effect
	Effect->CreateAnimation(Anim::effect_player_slash, ImgRes::effect_player_slash, 0.04f, false);
	Effect->SetFrameCallback(Anim::effect_player_slash, 4, [=] { Effect->SetActive(false); } );
}

void ADefaultPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}