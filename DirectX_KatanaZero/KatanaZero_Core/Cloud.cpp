#include "PreCompile.h"
#include "Cloud.h"

ACloud::ACloud()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	Body = CreateDefaultSubObject<USpriteRenderer>("Cloud");
	Body->SetupAttachment(Root);
	SetRoot(Root);
}

ACloud::~ACloud()
{
}

void ACloud::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);

	Body->CreateAnimation(
		Anim::effect_player_dustcloud, 
		ImgRes::effect_player_dustcloud,
		{ 0.08f, 0.08f, 0.08f, 0.08f, 0.06f, 0.06f, 0.06f },
		{ 0, 1, 2, 3, 4, 5, 6 },
		false);
	
	Body->ChangeAnimation(Anim::effect_player_dustcloud);
	Body->SetOrder(ERenderOrder::EffectFront);
	Body->SetAutoSize(2.5f, true);
}

void ACloud::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PosUpdate(_DeltaTime);

	if (true == Body->IsCurAnimationEnd())
	{
		Destroy();
	}
}
