#include "PreCompile.h"
#include "HeadHunterPhase2.h"

void AHeadHunterPhase2::PatternCheck()
{
}

// Pattern_GunShoot1
void AHeadHunterPhase2::GunShoot1Update(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		DelayCallBack(0.1f, [=]
			{
				Body->ChangeAnimation(Anim::headhunter_shoot_gun);

				EEngineDir Dir = Body->GetDir();
				switch (Dir)
				{
				case EEngineDir::Left:
					Body->SetPosition({ -37.0f, 0.0f, 0.0f });
					break;
				case EEngineDir::Right:
					Body->SetPosition({ 37.0f, 0.0f, 0.0f });
					break;
				}

				PatternOrder = 1;
			}
		);
	}
}

void AHeadHunterPhase2::GunShoot1Update1(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		PatternOrder = 0;
	}
}
