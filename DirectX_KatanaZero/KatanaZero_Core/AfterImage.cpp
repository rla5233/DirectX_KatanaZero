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

	if (0.0f < ActiveDelayTime)
	{
		ActiveDelayTime -= _DeltaTime;
		return;
	}

	MulColor.A -= TimeWeight * _DeltaTime;
	Body->SetPlusColor({ PlusColor.R, PlusColor.G, PlusColor.B });
	Body->SetMulColor({ MulColor.R, MulColor.G, MulColor.B, MulColor.A });

	if (0.0f > MulColor.A)
	{
		Destroy();
	}
}
