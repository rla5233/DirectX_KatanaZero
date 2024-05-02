#include "PreCompile.h"
#include "HitLaser.h"

AHitLaser::AHitLaser()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	
	Body = CreateDefaultSubObject<USpriteRenderer>("HitLaser");
	Body->SetupAttachment(Root);
	
	SetRoot(Root);
}

AHitLaser::~AHitLaser()
{
}

void AHitLaser::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);

	Body->SetOrder(ERenderOrder::EffectBack);
	Body->SetAutoSize(1.0f, true);
	Body->SetSprite(ImgRes::effect_hit_laser);
	Body->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.8f });

	DelayCallBack(0.25f, [=]
		{
			GEngine->SetOrderTimeScale(EUpdateOrder::Player, 1.0f);
			GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, 1.0f);
			GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, 1.0f);
			GEngine->SetOrderTimeScale(EUpdateOrder::Fan, 1.0f);
		}
	);

	DelayCallBack(0.5f, [=] 
		{ 
			Destroy();
		}
	);
}

void AHitLaser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PosUpdate(_DeltaTime);
}
