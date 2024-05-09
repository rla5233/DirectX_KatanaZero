#include "PreCompile.h"
#include "HeadHunterPhase2.h"

AHeadHunterPhase2::AHeadHunterPhase2()
{
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