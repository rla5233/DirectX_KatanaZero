#include "PreCompile.h"
#include "HeadHunterBase.h"

#include "PlayerBase.h"

AHeadHunterBase::AHeadHunterBase()
{
	UDefaultSceneComponent* Root= CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("HeadHunter_Body");
	Body->SetupAttachment(Root);

	BodyCol = CreateDefaultSubObject<UCollision>("BodyCol");
	BodyCol->SetupAttachment(Root);
	
	CreateCloudEffect();
	CreateRecoverEffect();

	SetRoot(Root);
}

void AHeadHunterBase::CreateRecoverEffect()
{
	AllRecoverEffect.reserve(20);
	for (size_t i = 0; i < AllRecoverEffect.capacity(); i++)
	{
		URecoverEffect NewRecoverEffect = URecoverEffect();
		NewRecoverEffect.Spark = CreateDefaultSubObject<USpriteRenderer>("Spark");
		NewRecoverEffect.Smoke = CreateDefaultSubObject<USpriteRenderer>("Smoke");

		NewRecoverEffect.Spark->SetOrder(ERenderOrder::EffectFront);
		NewRecoverEffect.Smoke->SetOrder(ERenderOrder::EffectFront);

		NewRecoverEffect.Spark->SetAutoSize(2.0f, true);
		NewRecoverEffect.Smoke->SetAutoSize(2.0f, true);
		
		NewRecoverEffect.Spark->CreateAnimation(Anim::effect_gun_spark1, ImgRes::effect_gun_spark1, 0.06f, false);
		NewRecoverEffect.Spark->CreateAnimation(Anim::effect_gun_spark2, ImgRes::effect_gun_spark2, 0.06f, false);
		NewRecoverEffect.Spark->CreateAnimation(Anim::effect_gun_spark3, ImgRes::effect_gun_spark3, 0.06f, false);
		NewRecoverEffect.Spark->SetFrameCallback(Anim::effect_gun_spark1, 8, [=] { NewRecoverEffect.Spark->SetActive(false); });
		NewRecoverEffect.Spark->SetFrameCallback(Anim::effect_gun_spark2, 8, [=] { NewRecoverEffect.Spark->SetActive(false); });
		NewRecoverEffect.Spark->SetFrameCallback(Anim::effect_gun_spark3, 8, [=] { NewRecoverEffect.Spark->SetActive(false); });

		NewRecoverEffect.Smoke->CreateAnimation(Anim::effect_gun_smoke1, ImgRes::effect_gun_smoke1, 0.04f, false);
		NewRecoverEffect.Smoke->CreateAnimation(Anim::effect_gun_smoke2, ImgRes::effect_gun_smoke2, 0.04f, false);
		NewRecoverEffect.Smoke->CreateAnimation(Anim::effect_gun_smoke3, ImgRes::effect_gun_smoke3, 0.04f, false);
		NewRecoverEffect.Smoke->SetFrameCallback(Anim::effect_gun_smoke1, 10, [=] { NewRecoverEffect.Smoke->SetActive(false); });
		NewRecoverEffect.Smoke->SetFrameCallback(Anim::effect_gun_smoke2, 12, [=] { NewRecoverEffect.Smoke->SetActive(false); });
		NewRecoverEffect.Smoke->SetFrameCallback(Anim::effect_gun_smoke3, 11, [=] { NewRecoverEffect.Smoke->SetActive(false); });

		NewRecoverEffect.Spark->SetActive(false);
		NewRecoverEffect.Smoke->SetActive(false);

		AllRecoverEffect.push_back(NewRecoverEffect);
	}
}

void AHeadHunterBase::CreateCloudEffect()
{
	Cloud.reserve(CloudSize);
	for (int i = 0; i < CloudSize; i++)
	{
		USpriteRenderer* NewRenderer = CreateDefaultSubObject<USpriteRenderer>("Cloud");
		UCloudEffect NewCloudEffect = UCloudEffect();
		NewCloudEffect.Renderer = NewRenderer;
		Cloud.push_back(NewCloudEffect);
	}

	for (size_t i = 0; i < Cloud.size(); i++)
	{
		Cloud[i].Renderer->CreateAnimation(
			Anim::effect_player_dustcloud,
			ImgRes::effect_player_dustcloud,
			{ 0.08f, 0.08f, 0.08f, 0.08f, 0.06f, 0.06f, 0.06f },
			{ 0, 1, 2, 3, 4, 5, 6 },
			false);
		Cloud[i].Renderer->SetFrameCallback(Anim::effect_player_dustcloud, 6, [=] { Cloud[i].Renderer->SetActive(false); });
		Cloud[i].Renderer->SetOrder(ERenderOrder::EffectBack);
		Cloud[i].Renderer->SetActive(false);
	}
}

AHeadHunterBase::~AHeadHunterBase()
{
}

void AHeadHunterBase::BeginPlay()
{
	Super::BeginPlay();

	URecordingObject::SetActor(this);
	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);
	UAfterImageObject::SetTargetRenderer(Body);

	RendererInit();
	CollisionInit();
	CreateAnimation();
	SoundInit();
	StateInit();
	SubStateInit();

	SetRecordingSize();
}

void AHeadHunterBase::RendererInit()
{
	Body->SetOrder(ERenderOrder::HeadHunter);
	Body->SetAutoSize(2.0f, true);
	Body->SetPivot(EPivot::BOT);
}

void AHeadHunterBase::CollisionInit()
{
	BodyCol->SetCollisionGroup(EColOrder::HeadHunter);
	BodyCol->SetCollisionType(ECollisionType::Rect);

	FVector BodyPos = { 0.0f, 45.0f, 0.0f };
	FVector BodyScale = { 50.0f, 90.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);
}

void AHeadHunterBase::CreateAnimation()
{
	Body->CreateAnimation(Anim::headhunter_idle, ImgRes::headhunter_idle, 0.1f, true);
	Body->CreateAnimation(Anim::headhunter_takeup_rifle, ImgRes::headhunter_takeup_rifle, 0.05f, false);
	Body->CreateAnimation(Anim::headhunter_putback_rifle, ImgRes::headhunter_takeup_rifle, 0.05f, false, 7, 0);
	Body->CreateAnimation(Anim::headhunter_hitfly, ImgRes::headhunter_hitfly, 0.04f, false);
	Body->CreateAnimation(Anim::headhunter_recover, ImgRes::headhunter_recover, 0.04f, false);
	Body->CreateAnimation(Anim::headhunter_exit_door, ImgRes::headhunter_exit_door, 0.08f, false);
	Body->CreateAnimation(Anim::headhunter_prejump, ImgRes::headhunter_prejump, 0.08f, false);
	Body->CreateAnimation(Anim::headhunter_jump, ImgRes::headhunter_jump, 0.0f, false);
	Body->CreateAnimation(Anim::headhunter_wall_idle, ImgRes::headhunter_wall_idle, 0.04f, false);
	Body->CreateAnimation(Anim::headhunter_wall_jump, ImgRes::headhunter_wall_jump, 0.11f, false);
	Body->CreateAnimation(Anim::headhunter_land , ImgRes::headhunter_land, 0.04f, false);
	Body->CreateAnimation(
		Anim::headhunter_roll, 
		ImgRes::headhunter_roll, 
		{ 0.05f, 0.05f, 0.05f, 0.05f, 0.08f, 0.05f, 0.05f },
		{ 0, 1, 2, 3, 4, 5, 6 },
		false);

	Body->SetLastFrameCallback(Anim::headhunter_putback_rifle,	[=] { State.ChangeState(HeadHunterState::idle); });
	Body->SetLastFrameCallback(Anim::headhunter_exit_door,		[=] { State.ChangeState(HeadHunterState::idle); });
	Body->SetLastFrameCallback(Anim::headhunter_roll,			[=] { State.ChangeState(HeadHunterState::idle); });
	Body->SetLastFrameCallback(Anim::headhunter_land,			[=] { State.ChangeState(HeadHunterState::idle); });
}

void AHeadHunterBase::SoundInit()
{
	Body->SetFrameCallback(Anim::headhunter_jump, 0,			[=] { UEngineSound::SoundPlay(SoundRes::hh_jump); });
	Body->SetFrameCallback(Anim::headhunter_wall_idle, 0,		[=] { UEngineSound::SoundPlay(SoundRes::player_land); });
	Body->SetFrameCallback(Anim::headhunter_wall_jump, 0,		[=] { USoundManager::SoundPlay_HH_Voice_WallJump(); });
	Body->SetFrameCallback(Anim::headhunter_hitfly, 0,			[=] { USoundManager::SoundPlay_HH_Voice_Hurt(); });
}

void AHeadHunterBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	SubState.Update(_DeltaTime);

	{
		std::string Msg = std::format("HeadHunter : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("HeadHunter : {}\n", State.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Head_HitCount : {}\n", HitCount);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void AHeadHunterBase::ColCheckUpdate()
{
	EEngineDir Dir = Body->GetDir();

	// OnGround
	if (true == IsOnGround(Dir))
	{
		OnGroundPosAdjust(Dir);
	}

	// CeilCol
	if (true == IsColHeadToCeil(Dir))
	{
		CeilColPosAdjust(Dir);
	}
}

void AHeadHunterBase::SetVelocityByDir(const FVector& _Vel)
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity = { -_Vel.X, _Vel.Y, _Vel.Z };
		break;
	case EEngineDir::Right:
		Velocity = { _Vel.X, _Vel.Y, _Vel.Z };
		break;
	}
}

void AHeadHunterBase::AddVelocityByDir(const FVector& _Vel)
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity += { -_Vel.X, _Vel.Y, _Vel.Z };
		break;
	case EEngineDir::Right:
		Velocity += { _Vel.X, _Vel.Y, _Vel.Z };
		break;
	}
}

void AHeadHunterBase::HitByPlayer(FVector _AttDir)
{
	if (true == IsDeadValue)
	{
		return;
	}

	HitDir = _AttDir;
	State.ChangeState(HeadHunterState::hitfly);
}