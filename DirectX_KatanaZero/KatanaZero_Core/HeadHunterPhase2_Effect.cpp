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
	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	FVector CurPos = GetActorLocation();
	float Rad = AirRifle1DegCount * UEngineMath::DToR;
	FVector ShootDir = { cosf(Rad), sinf(Rad), 0.0f };
	PlayLevel->SetShootBullet(CurPos, ShootDir);
	++AirRifle1ShootCount;
}