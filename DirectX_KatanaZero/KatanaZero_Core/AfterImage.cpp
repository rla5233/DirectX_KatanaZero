#include "PreCompile.h"
#include "AfterImage.h"

AAfterImage::AAfterImage()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("AfterImage");
	Body->SetupAttachment(Root);

	SetRoot(Root);
}

AAfterImage::~AAfterImage()
{
}

void AAfterImage::SetBodyInfo(USpriteRenderer* _Renderer)
{
	USpriteRenderer* ParentRenderer = _Renderer;
	
	Body->SetRotationDeg(ParentRenderer->GetLocalRotation());
	Body->SetPosition(ParentRenderer->GetLocalPosition());
	Body->SetSpriteInfo(ParentRenderer->GetCurInfo());
	Body->SetActive(ParentRenderer->IsActive());
	Body->SetDir(ParentRenderer->GetDir());

	Body->SetSamplering(ETextureSampling::LINEARCLAMP);
}

void AAfterImage::BeginPlay()
{
	Super::BeginPlay();

	Body->SetOrder(ERenderOrder::AfterImage);
	Body->SetAutoSize(2.0f, true); 
	Body->SetPivot(EPivot::BOT);
}

void AAfterImage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Color.A -= TimeWeight * _DeltaTime;

	float NextAlpha = Color.A - AlphaWeight;
	if (0.1f > NextAlpha)
	{
		NextAlpha = 0.1f;
	}

	Body->SetPlusColor({ Color.R, Color.G, Color.B });
	Body->SetMulColor({ 1.0f, 1.0f, 1.0f, NextAlpha });

	if (0.0f > Color.A)
	{
		Destroy();
	}
}
