#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
#include "MainCamera.h"

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

void AHeadHunterPhase2::SetAirRifle1Effect()
{
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

	if (false == IsAirRifleShake)
	{
		PlayLevel->GetKZMainCamera()->SetRetShakeTime(0.5f);
		PlayLevel->GetKZMainCamera()->SetRetShakeRange({ -10.0f, 10.0f, -10.0f, 10.0f });
		PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);
		IsAirRifleShake = true;
	}
}

void AHeadHunterPhase2::SetAirRifle2Effect()
{
	AllRifleLaserAlpha[RifleLaserIdx] = 1.0f;
	
	AllRifleLaserEffect[RifleLaserIdx]->AnimationReset();
	AllRifleLaserEffect[RifleLaserIdx]->SetSprite(ImgRes::compo_bullet);
	AllRifleLaserEffect[RifleLaserIdx]->SetScale({ 720.0f, 2.0f, 1.0f });
	AllRifleLaserEffect[RifleLaserIdx]->SetPosition({ 419.0f, 56.0f, 0.0f });
	AllRifleLaserEffect[RifleLaserIdx]->SetActive(true);
	AllRifleLaserEffect[RifleLaserIdx]->SetMulColor({ 1.0f, 1.0f, 1.0f, AllRifleLaserAlpha[RifleLaserIdx] });
}

void AHeadHunterPhase2::SetAirRifle2Effect1()
{
	float Deg = 0.0f;
	AllRifleLaserEffect[RifleLaserIdx]->ChangeAnimation(Anim::effect_laser);
	AllRifleLaserEffect[RifleLaserIdx]->SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	AllRifleLaserEffect[RifleLaserIdx]->SetScale({ 1280.0f, 18.0f, 1.0f });
	AllRifleLaserEffect[RifleLaserIdx]->SetRotationDeg({ 0.0f, 0.0f, Deg });
	Deg *= UEngineMath::DToR;
	AllRifleLaserEffect[RifleLaserIdx]->SetPosition({ 690.0f * cosf(Deg), 690.0f * sinf(Deg) + 56.0f, 0.0f });
	AirRifle2TimeCount = 0.0f;
}