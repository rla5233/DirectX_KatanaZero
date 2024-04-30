#include "PreCompile.h"
#include "UpMark.h"

AUpMark::AUpMark()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	Body = CreateDefaultSubObject<USpriteRenderer>("Mark");
	Body->SetupAttachment(Root);
	SetRoot(Root);
}

AUpMark::~AUpMark()
{
}

void AUpMark::BeginPlay()
{
	Super::BeginPlay();

	Body->CreateAnimation(Anim::effect_enemy_follow, ImgRes::effect_enemy_follow, 0.1f, false);
	Body->ChangeAnimation(Anim::effect_enemy_follow);
	Body->SetOrder(ERenderOrder::EffectBack);
	Body->SetAutoSize(2.0f, true);
}

void AUpMark::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

