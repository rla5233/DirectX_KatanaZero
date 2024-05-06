#include "PreCompile.h"
#include "HeadHunterBase.h"

#include "HeadHunterLevel.h"
#include "MainCamera.h"

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