#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"

void AHeadHunterPhase2::SetRifle1LaserEffect()
{
	AllRifleLaserEffect[RifleLaserIdx]->AnimationReset();
	AllRifleLaserEffect[RifleLaserIdx]->SetSprite(ImgRes::compo_bullet);
	AllRifleLaserEffect[RifleLaserIdx]->SetScale({ 0.0f, 2.0f, 1.0f });
	AllRifleLaserEffect[RifleLaserIdx]->SetRotationDeg(FVector::Zero);

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		AllRifleLaserEffect[RifleLaserIdx]->SetPosition({ -41.0f, 56.0f ,0.0f });
		break;
	case EEngineDir::Right:
		AllRifleLaserEffect[RifleLaserIdx]->SetPosition({ 41.0f, 56.0f ,0.0f });
		break;
	}

	AllRifleLaserEffect[RifleLaserIdx]->SetActive(true);
	PatternOrder = 1;
	DelayCallBack(0.5f, [=] { PatternOrder = 2; });
}

void AHeadHunterPhase2::SetAirRifleEffect()
{
	//GEngine->SetGlobalTimeScale(0.1f);
	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	float Rad = AirRifle1DegCount * UEngineMath::DToR;
	FVector CurPos = GetActorLocation();
	CurPos += {70.0f * cosf(Rad), 70.0f * sinf(Rad) + 40.0f, 0.0f};
	FVector ShootDir = { cosf(Rad), sinf(Rad), 0.0f };
	PlayLevel->SetShootBullet(CurPos , ShootDir);
	++AirRifle1ShootCount;

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	AllSparkEffect[SparkIdx]->AnimationReset();
	switch (RandomValue)
	{
	case 1:
		AllSparkEffect[SparkIdx]->ChangeAnimation(Anim::effect_gun_spark1);
		break;
	case 2:
		AllSparkEffect[SparkIdx]->ChangeAnimation(Anim::effect_gun_spark2);
		break;
	case 3:
		AllSparkEffect[SparkIdx]->ChangeAnimation(Anim::effect_gun_spark3);
		break;
	}

	AllSparkEffect[SparkIdx]->SetPosition(GetActorLocation());
	AllSparkEffect[SparkIdx]->AddPosition({ 70.0f * cosf(Rad), 70.0f * sinf(Rad) + 40.0f ,0.0f });
	AllSparkEffect[SparkIdx]->SetRotationDeg({ 0.0f, 0.0f, AirRifle1DegCount });
	AllSparkEffect[SparkIdx]->SetActive(true);
	SparkIdxUpdate();
}