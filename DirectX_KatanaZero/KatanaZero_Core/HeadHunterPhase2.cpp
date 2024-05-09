#include "PreCompile.h"
#include "HeadHunterPhase2.h"

AHeadHunterPhase2::AHeadHunterPhase2()
{
	DashLaser = CreateDefaultSubObject<USpriteRenderer>("DashLaser");
	DashLaser->SetSprite(ImgRes::effect_dash_laser);
	DashLaser->SetOrder(ERenderOrder::EffectBack);
	DashLaser->SetupAttachment(GetRoot());
	DashLaser->SetActive(false);
}

AHeadHunterPhase2::~AHeadHunterPhase2()
{
}

void AHeadHunterPhase2::BeginPlay()
{
	Super::BeginPlay();

	Hp = 10;
}

void AHeadHunterPhase2::CreateAnimation()
{
	Super::CreateAnimation();

	Body->CreateAnimation(Anim::headhunter_shoot_gun, ImgRes::headhunter_shoot_gun, 0.08f, false);
	Body->CreateAnimation(Anim::headhunter_takeout_gun, ImgRes::headhunter_takeout_gun, 0.06f, false);
	Body->CreateAnimation(Anim::headhunter_putback_gun, ImgRes::headhunter_takeout_gun, 0.08f, false, 6, 0);
	Body->CreateAnimation(Anim::headhunter_predash, ImgRes::headhunter_predash, 0.06f, false);

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