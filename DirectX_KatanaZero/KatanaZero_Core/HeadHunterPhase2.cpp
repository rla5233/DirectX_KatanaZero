#include "PreCompile.h"
#include "HeadHunterPhase2.h"

AHeadHunterPhase2::AHeadHunterPhase2()
{
	CreateDashLaser();
	CreateDashAttack();
}

AHeadHunterPhase2::~AHeadHunterPhase2()
{
}

void AHeadHunterPhase2::BeginPlay()
{
	Super::BeginPlay();

	Hp = 10;
}

void AHeadHunterPhase2::CreateDashLaser()
{
	DashLaser = CreateDefaultSubObject<USpriteRenderer>("DashLaser");
	DashLaser->SetSprite(ImgRes::effect_dash_laser);
	DashLaser->SetOrder(ERenderOrder::EffectBack);
	DashLaser->SetupAttachment(GetRoot());
	DashLaser->SetActive(false);
}

void AHeadHunterPhase2::CreateDashAttack()
{
	DashAttack = CreateDefaultSubObject<UCollision>("DashAttack");
	DashAttack->SetCollisionType(ECollisionType::Rect);
	DashAttack->SetCollisionGroup(EColOrder::EnemyAttack);
	DashAttack->SetScale({ 50.0f, 90.0f, 1.0f });
	DashAttack->SetPosition({ 0.0f, 45.0f, 0.0f });
	DashAttack->SetupAttachment(GetRoot());
	DashAttack->SetActive(false);
}

void AHeadHunterPhase2::CreateAnimation()
{
	Super::CreateAnimation();

	Body->CreateAnimation(Anim::headhunter_shoot_gun, ImgRes::headhunter_shoot_gun, 0.08f, false);
	Body->CreateAnimation(Anim::headhunter_takeout_gun, ImgRes::headhunter_takeout_gun, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_putback_gun, ImgRes::headhunter_takeout_gun, 0.08f, false, 6, 0);
	Body->CreateAnimation(Anim::headhunter_predash, ImgRes::headhunter_predash, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_dashend, ImgRes::headhunter_dashend, 0.06f, false);

	Body->SetLastFrameCallback(Anim::headhunter_putback_gun, [=] 
		{ 
			Body->SetPosition(FVector::Zero);
			State.ChangeState(HeadHunterState::idle);
		}
	);
}

void AHeadHunterPhase2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunterPhase2::AdjustBodyPosByDir(const FVector _Pos)
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetPosition({ -_Pos.X, _Pos.Y, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ _Pos.X, _Pos.Y, 0.0f });
		break;
	}
}