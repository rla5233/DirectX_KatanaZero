#include "PreCompile.h"
#include "HeadHunterPhase1.h"

void AHeadHunterPhase1::SetRifle1LaserEffect()
{
	LaserEffect->SetSprite(ImgRes::compo_bullet);
	LaserEffect->SetScale({ 0.0f, 2.0f, 1.0f });
	LaserEffect->SetRotationDeg(FVector::Zero);

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
	LaserEffect->SetScale({ 1280.0f, 20.0f, 1.0f });
	LaserEffect->SetActive(true);
	LaserCol->SetActive(true);
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
		Deg = 5.0f;
		LaserEffect->SetRotationDeg({ 0.0f, 0.0f, Deg });
		Deg *= UEngineMath::DToR;
		LaserEffect->SetPosition({ 690.0f * cosf(Deg), 690.0f * sinf(Deg) + 60, 0.0f });
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
		LaserEffect->AddRotationDeg({ 0.0f, 0.0f, -400.0f * _DeltaTime });
		Deg = LaserEffect->GetWorldRotation().Z * UEngineMath::DToR;
		LaserEffect->SetPosition({ 690.0f * cosf(Deg), 690.0f * sinf(Deg) + 60, 0.0f });
		break;
	}
}