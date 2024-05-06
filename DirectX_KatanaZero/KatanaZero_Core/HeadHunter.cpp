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

	SetRoot(Root);
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
}

void AHeadHunter::CreateAnimation()
{
	Body->CreateAnimation(Anim::headhunter_idle, ImgRes::headhunter_idle, 0.1f, true);
	Body->CreateAnimation(Anim::headhunter_takeup_rifle, ImgRes::headhunter_takeup_rifle, 0.05f, false);
	Body->CreateAnimation(Anim::headhunter_putback_rifle, ImgRes::headhunter_takeup_rifle, 0.05f, false, 7, 0);

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