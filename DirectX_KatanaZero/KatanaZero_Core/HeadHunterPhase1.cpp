#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"
#include "PlayerBase.h"
#include "MainCamera.h"

AHeadHunterPhase1::AHeadHunterPhase1()
{
	LaserEffect = CreateDefaultSubObject<USpriteRenderer>("LaserEffect");
	LaserEffect->SetupAttachment(GetRoot());

	LaserCol = CreateDefaultSubObject<UCollision>("LaserCol");
	LaserCol->SetupAttachment(LaserEffect);

	CreateLaserEffect();
}

AHeadHunterPhase1::~AHeadHunterPhase1()
{
}

void AHeadHunterPhase1::BeginPlay()
{
	Super::BeginPlay();
}


void AHeadHunterPhase1::CollisionInit()
{
	Super::CollisionInit();

	LaserCol->SetCollisionGroup(EColOrder::EnemyAttack);
	LaserCol->SetCollisionType(ECollisionType::RotRect);
	LaserCol->SetActive(false);
}

void AHeadHunterPhase1::CreateLaserEffect()
{
	LaserEffect->SetOrder(ERenderOrder::EffectFront);
	LaserEffect->SetActive(false);

	LaserEffect->CreateAnimation(Anim::effect_laser, ImgRes::effect_laser, 0.1f, true);
}

void AHeadHunterPhase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


// Sub State
void AHeadHunterPhase1::PlayStart()
{
	State.ChangeState(HeadHunterState::pattern_rifle1);
}

void AHeadHunterPhase1::RestartStart()
{
	Super::RestartStart();

	LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.0f });
}

void AHeadHunterPhase1::LaserColCheck()
{
	LaserCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision>(_Other))
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			FVector PlayerPos = Player->GetActorLocation();
			FVector CurPos = GetActorLocation();
			Player->HitByEnemy(PlayerPos - CurPos, EEnemyType::HeadHunterLaser);
		}
	);
}