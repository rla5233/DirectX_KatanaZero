#include "PreCompile.h"
#include "HeadHunter.h"

void AHeadHunter::SetRifle1LaserEffect()
{
	LaserEffect->SetSprite(ImgRes::compo_bullet);
	LaserEffect->SetScale({ 0.0f, 2.0f, 0.0f });
	
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

void AHeadHunter::Rifle1LaserEffectUpdate1(float _DeltaTime)
{
	FVector CurScale = LaserEffect->GetLocalScale();
	if (1280.0f < CurScale.X)
	{
		return;
	}

	float AddScaleX = 5000.0f *_DeltaTime;
	LaserEffect->AddScale({ AddScaleX, 0.0f, 0.0f });
	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		LaserEffect->AddPosition({ -AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	case EEngineDir::Right:
		LaserEffect->AddPosition({ AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	}
}

void AHeadHunter::Rifle1LaserEffectUpdate2(float _DeltaTime)
{
	LaserAlpha -= 9.0f * _DeltaTime;

	if (0.0f > LaserAlpha)
	{
		LaserAlpha = 0.0f;
		PatternOrder = -1;
		LaserEffect->SetActive(false);
		DelayCallBack(0.04f, [=]
			{
				LaserAlpha = 1.0f;
				LaserEffect->SetActive(true);
				LaserEffect->ChangeAnimation(Anim::effect_laser);
				LaserEffect->AddScale({ 0.0f, 14.0f, 0.0f });
				LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
				switch (Body->GetDir())
				{
				case EEngineDir::Left:
					LaserEffect->SetRotationDeg({ 0.0f, 180.0f, 0.0f });
					break;
				case EEngineDir::Right:
					LaserEffect->SetRotationDeg({ 0.0f, 0.0f, 0.0f });
					break;
				}

				LaserCol->SetActive(true);

				DelayCallBack(0.1f, [=]
					{
						PatternOrder = 3;
					}
				);
			}
		);
	}

	LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
}

void AHeadHunter::Rifle1LaserEffectUpdate3(float _DeltaTime)
{
	if (false == LaserEffect->IsActive())
	{
		return;
	}

	float AddScaleY = -100.0f * _DeltaTime;
	LaserEffect->AddScale({ 0.0f, AddScaleY, 0.0f });

	FVector CurScale = LaserEffect->GetLocalScale();
	if (0.0f > CurScale.Y)
	{
		LaserCol->SetActive(false);
		LaserEffect->SetActive(false);
		Body->ChangeAnimation(Anim::headhunter_putback_rifle);
		return;
	}
}
