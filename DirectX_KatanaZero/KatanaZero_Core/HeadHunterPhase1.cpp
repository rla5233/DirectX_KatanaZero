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

void AHeadHunterPhase1::CreateRollCroudEffect(float _DeltaTime)
{
	if (0.0f < CroudTimeCount)
	{
		CroudTimeCount -= _DeltaTime;
		return;
	}
	
	if (true == Cloud[CloudIdx].Renderer->IsActive())
	{
		return;
	}

	Cloud[CloudIdx].Renderer->AnimationReset();
	Cloud[CloudIdx].Renderer->ChangeAnimation(Anim::effect_player_dustcloud);
	Cloud[CloudIdx].Renderer->SetAutoSize(2.0f, true);
	Cloud[CloudIdx].Renderer->SetActive(true);

	float Deg = UEngineRandom::MainRandom.RandomFloat(5.0f, 35.0f);
	Deg *= UEngineMath::DToR;
	FVector VelDir = { cosf(Deg), sinf(Deg), 0.0f };

	float Speed = UEngineRandom::MainRandom.RandomFloat(100.0f, 250.0f);

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Cloud[CloudIdx].Renderer->SetPosition(GetActorLocation() + FVector(20.0f, 5.0f, 0.0f));
		break;
	case EEngineDir::Right:
		Cloud[CloudIdx].Renderer->SetPosition(GetActorLocation() + FVector(-20.0f, 5.0f, 0.0f));
		VelDir.X *= -1;
		break;
	}

	Cloud[CloudIdx].Velocity = VelDir * Speed;

	++CloudIdx;
	if (CloudSize <= CloudIdx)
	{
		CloudIdx = 0;
	}
	
	CroudTimeCount = Const::effect_roll_cloud_delay;
}

void AHeadHunterPhase1::CroudEffectUpdate(float _DeltaTime)
{
	for (size_t i = 0; i < Cloud.size(); i++)
	{
		if (false == Cloud[i].Renderer->IsActive())
		{
			continue;
		}

		Cloud[i].Renderer->AddPosition(Cloud[i].Velocity * _DeltaTime);
	}
}
