#include "PreCompile.h"
#include "HeadHunter.h"

#include "PlayerBase.h"

AHeadHunter::AHeadHunter()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("HeadHunter_Body");
	Body->SetupAttachment(Root);

	LaserEffect = CreateDefaultSubObject<USpriteRenderer>("LaserEffect");
	LaserEffect->SetupAttachment(Root);

	LaserCol = CreateDefaultSubObject<UCollision>("LaserCol");
	LaserCol->SetupAttachment(LaserEffect);

	BodyCol = CreateDefaultSubObject<UCollision>("BodyCol");
	BodyCol->SetupAttachment(Root);

	CreateRecoverEffect();

	SetRoot(Root);
}

void AHeadHunter::CreateRecoverEffect()
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
		NewRecoverEffect.Spark->SetLastFrameCallback(Anim::effect_gun_spark1, [=] { NewRecoverEffect.Spark->SetActive(false); });
		NewRecoverEffect.Spark->SetLastFrameCallback(Anim::effect_gun_spark2, [=] { NewRecoverEffect.Spark->SetActive(false); });
		NewRecoverEffect.Spark->SetLastFrameCallback(Anim::effect_gun_spark3, [=] { NewRecoverEffect.Spark->SetActive(false); });

		NewRecoverEffect.Smoke->CreateAnimation(Anim::effect_gun_smoke1, ImgRes::effect_gun_smoke1, 0.04f, false);
		NewRecoverEffect.Smoke->CreateAnimation(Anim::effect_gun_smoke2, ImgRes::effect_gun_smoke2, 0.04f, false);
		NewRecoverEffect.Smoke->CreateAnimation(Anim::effect_gun_smoke3, ImgRes::effect_gun_smoke3, 0.04f, false);
		NewRecoverEffect.Smoke->SetLastFrameCallback(Anim::effect_gun_smoke1, [=] { NewRecoverEffect.Smoke->SetActive(false); });
		NewRecoverEffect.Smoke->SetLastFrameCallback(Anim::effect_gun_smoke2, [=] { NewRecoverEffect.Smoke->SetActive(false); });
		NewRecoverEffect.Smoke->SetLastFrameCallback(Anim::effect_gun_smoke3, [=] { NewRecoverEffect.Smoke->SetActive(false); });

		NewRecoverEffect.Spark->SetActive(false);
		NewRecoverEffect.Smoke->SetActive(false);

		AllRecoverEffect.push_back(NewRecoverEffect);
	}
}

AHeadHunter::~AHeadHunter()
{
}

void AHeadHunter::BeginPlay()
{
	Super::BeginPlay();

	URecordingObject::SetActor(this);
	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);

	RendererInit();
	CollisionInit();
	CreateAnimation();
	StateInit();
	SubStateInit();

	SetRecordingSize();
}

void AHeadHunter::RendererInit()
{
	Body->SetOrder(ERenderOrder::HeadHunter);
	Body->SetAutoSize(2.0f, true);
	Body->SetPivot(EPivot::BOT);

	LaserEffect->SetOrder(ERenderOrder::EffectFront);
	LaserEffect->SetActive(false);
}

void AHeadHunter::CollisionInit()
{
	LaserCol->SetCollisionGroup(EColOrder::EnemyAttack);
	LaserCol->SetCollisionType(ECollisionType::RotRect);
	LaserCol->SetActive(false);

	BodyCol->SetCollisionGroup(EColOrder::HeadHunter);
	BodyCol->SetCollisionType(ECollisionType::Rect);

	FVector BodyPos = { 0.0f, 45.0f, 0.0f };
	FVector BodyScale = { 50.0f, 90.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);

	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);
}

void AHeadHunter::CreateAnimation()
{
	Body->CreateAnimation(Anim::headhunter_idle, ImgRes::headhunter_idle, 0.1f, true);
	Body->CreateAnimation(Anim::headhunter_takeup_rifle, ImgRes::headhunter_takeup_rifle, 0.05f, false);
	Body->CreateAnimation(Anim::headhunter_putback_rifle, ImgRes::headhunter_takeup_rifle, 0.05f, false, 7, 0);
	Body->CreateAnimation(Anim::headhunter_hitfly, ImgRes::headhunter_hitfly, 0.04f, false);
	Body->CreateAnimation(Anim::headhunter_recover, ImgRes::headhunter_recover, 0.04f, false);

	Body->SetLastFrameCallback(Anim::headhunter_takeup_rifle, [=]
		{
			SetRifle1LaserEffect();
		}
	);

	Body->SetLastFrameCallback(Anim::headhunter_putback_rifle, [=]
		{
			State.ChangeState(HeadHunterState::idle);
		}
	);

	LaserEffect->CreateAnimation(Anim::effect_laser, ImgRes::effect_laser, 0.1f, true);
}

void AHeadHunter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	SubState.Update(_DeltaTime);

	{
		std::string Msg = std::format("HeadHunter : {}\n", State.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void AHeadHunter::LaserColCheck()
{
	LaserCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision>(_Other))
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			Player->HitByEnemy(EEnemyType::HeadHunterLaser);
		}
	);
}

void AHeadHunter::ColCheckUpdate()
{
	EEngineDir Dir = Body->GetDir();

	// OnGround
	if (true == IsOnGround(Dir))
	{
		OnGroundPosAdjust(Dir);
	}
}

void AHeadHunter::HitByPlayer(FVector _AttDir)
{
	HitDir = _AttDir;
	State.ChangeState(HeadHunterState::hitfly);
}