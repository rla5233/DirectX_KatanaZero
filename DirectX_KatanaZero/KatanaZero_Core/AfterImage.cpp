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

	Body->SetSamplering(ETextureSampling::LINEAR);
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

	Alpha -= TimeWeight * _DeltaTime;
	Body->SetMulColor({ 1.0f, 1.0f, 1.0f, Alpha });

	if (0.0f > Alpha)
	{
		Destroy();
	}
}
