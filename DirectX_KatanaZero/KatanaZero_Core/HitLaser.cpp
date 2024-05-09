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
	Order = 0;
}

void AHitLaser::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	switch (Order)
	{
	case 0:
		Body->SetOrder(ERenderOrder::EffectBack);
		Body->SetAutoSize(1.0f, true);
		Body->SetSprite(ImgRes::effect_hit_laser);
		Body->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.8f });
		
		switch (Type)
		{
		case EHitLaserType::Default:
			UContentsHelper::SetHitLaserTimeScale(Type);
			DelayCallBack(0.25f, [=] { UContentsHelper::ResetTimeScale(); });
			break;
		case EHitLaserType::HeadHunterDash:
			UContentsHelper::SetHitLaserTimeScale(Type);
			DelayCallBack(0.3f, [=] { UContentsHelper::ResetTimeScale(); });
			break;
		}


		DelayCallBack(0.5f, [=]
			{
				Destroy();
			}
		);

		Order = 1;
		break;
	case 1:
		PosUpdate(_DeltaTime);
		break;
	}

}
