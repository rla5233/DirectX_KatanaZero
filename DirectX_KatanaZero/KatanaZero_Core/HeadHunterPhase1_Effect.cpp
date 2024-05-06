#include "PreCompile.h"
#include "HeadHunterPhase1.h"

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

void AHeadHunterPhase1::SetRifle1LaserEffect()
{
	LaserEffect->SetSprite(ImgRes::compo_bullet);
	LaserEffect->SetScale({ 0.0f, 2.0f, 1.0f });

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		LaserEffect->SetPosition({ -41.0f, 56.0f ,0.0f });
		break;
	case EEngineDir::Right:
		LaserEffect->SetPosition({ 41.0f, 56.0f ,0.0f });
		break;
	}

	LaserEffect->SetActive(true);
	PatternOrder = 1;

	DelayCallBack(0.5f, [=] { PatternOrder = 2; });
}
