#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"
#include "PlayerBase.h"

AHeadHunterPhase1::AHeadHunterPhase1()
{
	LaserEffect = CreateDefaultSubObject<USpriteRenderer>("LaserEffect");
	LaserEffect->SetupAttachment(GetRoot());

	LaserCol = CreateDefaultSubObject<UCollision>("LaserCol");
	LaserCol->SetupAttachment(LaserEffect);

	CreateLaserEffect();
	CreateCloudEffect();
}

AHeadHunterPhase1::~AHeadHunterPhase1()
{
}

void AHeadHunterPhase1::BeginPlay()
{
	Super::BeginPlay();

	Hp = 3;
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

void AHeadHunterPhase1::CreateCloudEffect()
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

void AHeadHunterPhase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


// Sub State
void AHeadHunterPhase1::PlayStart()
{
	State.ChangeState(HeadHunterState::pattern_rifle1);
}

void AHeadHunterPhase1::Play(float _DeltaTime)
{
	Super::Play(_DeltaTime);

	CroudEffectUpdate(_DeltaTime);
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