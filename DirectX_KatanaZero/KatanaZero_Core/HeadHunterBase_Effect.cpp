#include "PreCompile.h"
#include "HeadHunterBase.h"

#include "HeadHunterLevel.h"
#include "MainCamera.h"

void AHeadHunterBase::SetRollCroudEffect(float _DeltaTime)
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

void AHeadHunterBase::CroudEffectUpdate(float _DeltaTime)
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

void AHeadHunterBase::SetRecoverEffect()
{
	FVector CurPos = GetActorLocation();

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		CurPos += { 0.0f, 0.0f, 0.0f };
		break;
	case EEngineDir::Right:
		CurPos += { 0.0f, 0.0f, 0.0f };
		break;
	}

	for (size_t i = 0; i < AllRecoverEffect.size(); i++)
	{
		float Deg = UEngineRandom::MainRandom.RandomFloat(0.0f, 180.0f);
		AllRecoverEffect[i].SetEffectRotationDeg({ 0.0f , 0.0f, Deg });

		Deg *= UEngineMath::DToR;
		FVector Pos = FVector(cosf(Deg), sinf(Deg), 0.0f);

		float SparkPos = UEngineRandom::MainRandom.RandomFloat(0.0f, 180.0f);
		AllRecoverEffect[i].Spark->SetPosition(CurPos + FVector(SparkPos, SparkPos, 0.0f) * Pos);

		float SmokePos = UEngineRandom::MainRandom.RandomFloat(0.0f, 150.0f);
		AllRecoverEffect[i].Smoke->SetPosition(CurPos + FVector(SmokePos, SmokePos, 0.0f) * Pos);
		
		int SparkType = UEngineRandom::MainRandom.RandomInt(1, 3);
		switch (SparkType)
		{
		case 1:
			AllRecoverEffect[i].Spark->ChangeAnimation(Anim::effect_gun_spark1);
			break;
		case 2:
			AllRecoverEffect[i].Spark->ChangeAnimation(Anim::effect_gun_spark2);
			break;
		case 3:
			AllRecoverEffect[i].Spark->ChangeAnimation(Anim::effect_gun_spark3);
			break;
		}

		int Smokeype = UEngineRandom::MainRandom.RandomInt(1, 3);
		switch (SparkType)
		{
		case 1:
			AllRecoverEffect[i].Smoke->ChangeAnimation(Anim::effect_gun_smoke1);
			break;
		case 2:
			AllRecoverEffect[i].Smoke->ChangeAnimation(Anim::effect_gun_smoke2);
			break;
		case 3:
			AllRecoverEffect[i].Smoke->ChangeAnimation(Anim::effect_gun_smoke3);
			break;
		}

		AllRecoverEffect[i].SetEffectActive(true);
	}
}