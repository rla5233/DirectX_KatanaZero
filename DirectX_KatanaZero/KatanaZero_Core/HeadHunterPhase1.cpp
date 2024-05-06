#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"

AHeadHunterPhase1::AHeadHunterPhase1()
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

AHeadHunterPhase1::~AHeadHunterPhase1()
{
}

void AHeadHunterPhase1::BeginPlay()
{
	Super::BeginPlay();
}

void AHeadHunterPhase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AHeadHunterPhase1::Play(float _DeltaTime)
{
	Super::Play(_DeltaTime);

	CroudEffectUpdate(_DeltaTime);
}
