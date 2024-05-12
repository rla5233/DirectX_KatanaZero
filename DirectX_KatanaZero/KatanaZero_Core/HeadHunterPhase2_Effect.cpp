#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
#include "MainCamera.h"

void AHeadHunterPhase2::SetRifle1LaserEffect()
{
	RifleLaserEffect->AnimationReset();
	RifleLaserEffect->SetSprite(ImgRes::compo_bullet);
	RifleLaserEffect->SetScale({ 0.0f, 2.0f, 1.0f });
	RifleLaserEffect->SetRotationDeg(FVector::Zero);

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		RifleLaserEffect->SetPosition({ -41.0f, 56.0f ,0.0f });
		break;
	case EEngineDir::Right:
		RifleLaserEffect->SetPosition({ 41.0f, 56.0f ,0.0f });
		break;
	}

	RifleLaserEffect->SetActive(true);
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
	RifleLaserAlpha = 1.0f;
	
	RifleLaserEffect->AnimationReset();
	RifleLaserEffect->SetSprite(ImgRes::compo_bullet);
	RifleLaserEffect->SetScale({ 720.0f, 2.0f, 1.0f });
	RifleLaserEffect->SetPosition({ 419.0f, 56.0f, 0.0f });
	RifleLaserEffect->SetActive(true);
	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, RifleLaserAlpha });
}

void AHeadHunterPhase2::SetAirRifle2Effect1()
{
	float Deg = 0.0f;
	RifleLaserEffect->ChangeAnimation(Anim::effect_laser);
	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	RifleLaserEffect->SetScale({ 1280.0f, 18.0f, 1.0f });
	RifleLaserEffect->SetRotationDeg({ 0.0f, 0.0f, Deg });
	Deg *= UEngineMath::DToR;
	AirRifle2TimeCount = 0.0f;
}

void AHeadHunterPhase2::SetComplexLaser1Effect()
{
	RifleLaserAlpha = 1.0f;
	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, RifleLaserAlpha });

	float Deg = SweepLaserDeg1;
	RifleLaserEffect->SetScale({ 720.0f, 2.0f, 1.0f });
	RifleLaserEffect->SetRotationDeg({ 0.0f, 0.0f, SweepLaserDeg1 });

	float Rad = Deg * UEngineMath::DToR;
	FVector Dir = { cosf(Rad), sinf(Rad), 0.0f };
	Dir *= 360.0f;
	RifleLaserEffect->SetPosition({ Dir.X - 20.0f, Dir.Y - 10.0f, 0.0f });
	
	RifleLaserEffect->AnimationReset();
	RifleLaserEffect->SetSprite(ImgRes::compo_bullet);
	RifleLaserEffect->SetActive(true);
}

void AHeadHunterPhase2::SetComplexLaser2Effect()
{
	RifleLaserAlpha = 1.0f;
	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, RifleLaserAlpha });

	float Deg = SweepLaserDeg2;
	RifleLaserEffect->SetScale({ 720.0f, 2.0f, 1.0f });
	RifleLaserEffect->SetRotationDeg({ 0.0f, 0.0f, SweepLaserDeg2 });

	float Rad = Deg * UEngineMath::DToR;
	FVector Dir = { cosf(Rad), sinf(Rad), 0.0f };
	Dir *= 360.0f;
	RifleLaserEffect->SetPosition({ Dir.X + 20.0f, Dir.Y - 10.0f, 0.0f });

	RifleLaserEffect->AnimationReset();
	RifleLaserEffect->SetSprite(ImgRes::compo_bullet);
	RifleLaserEffect->SetActive(true);
}

void AHeadHunterPhase2::SetBombingEffect()
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetDir(EEngineDir::Right);
		SetVelocityByDir({ 1000.0f, 80.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetDir(EEngineDir::Left);
		SetVelocityByDir({ 1000.0f, 80.0f, 0.0f });
		break;
	}

	Body->ChangeAnimation(Anim::headhunter_diefly_stop);
	PatternOrder = 2;
}