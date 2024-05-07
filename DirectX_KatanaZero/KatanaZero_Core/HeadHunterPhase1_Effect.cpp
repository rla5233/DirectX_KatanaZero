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

void AHeadHunterPhase1::SetAirRifle1LaserEffect()
{
	LaserEffect->ChangeAnimation(Anim::effect_laser);
	LaserEffect->SetScale({ 1280.0f, 14.0f, 1.0f });
	LaserEffect->SetActive(true);
	float Deg = 0.0f;

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		Deg = 175.0f;
		LaserEffect->SetRotationDeg({ 0.0f, 0.0f, Deg });
		
		Deg *= UEngineMath::DToR;
		LaserEffect->SetPosition({ 690.0f * cosf(Deg), 690.0f * sinf(Deg) + 60, 0.0f});
	

		break;
	case EEngineDir::Right:
		LaserEffect->SetRotationDeg({ 0.0f, 0.0f, 270.0f });
		LaserEffect->SetPosition({ 41.0f, 56.0f ,0.0f });
		break;
	}
}

void AHeadHunterPhase1::AirRifle1LaserEffectUpdate(float _DeltaTime)
{
	float Deg = 0.0f;

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		LaserEffect->AddRotationDeg({ 0.0f, 0.0f, 400.0f * _DeltaTime });
		Deg = LaserEffect->GetWorldRotation().Z * UEngineMath::DToR;
		LaserEffect->SetPosition({ 690.0f * cosf(Deg), 690.0f * sinf(Deg) + 60, 0.0f });

		break;
	case EEngineDir::Right:
		//LaserEffect->SetPosition({ 41.0f, 56.0f ,0.0f });
		break;
	}
}