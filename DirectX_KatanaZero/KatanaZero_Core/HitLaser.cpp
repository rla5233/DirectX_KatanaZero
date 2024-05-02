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
	UContentsHelper::SetHitLaserTimeScale();

	DelayCallBack(0.25f, [=]
		{
			UContentsHelper::ResetTimeScale();
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
