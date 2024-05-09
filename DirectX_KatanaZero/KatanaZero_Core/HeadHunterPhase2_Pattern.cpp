#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
#include "PlayerBase.h"

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
				if (HeadHunterState::pattern_gunshoot1 != State.GetCurStateName())
				{
					return;
				}

				Body->AnimationReset();
				Body->ChangeAnimation(Anim::headhunter_shoot_gun);
				AdjustBodyPosByDir({ 39.0f, 0.0f, 0.0f });
				PatternOrder = 1;
			}
		);
	}
}

void AHeadHunterPhase2::GunShoot1Update1(float _DeltaTime)
{
	AHeadHunterLevel_Phase2* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase2*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	FVector CurPos = GetActorLocation();
	float Diff_X = abs(PlayerPos.X - CurPos.X);

	if (2 == Body->GetCurAnimationFrame() && false == IsGunShoot)
	{
		FVector CurScale = Body->GetWorldScale();

		FVector ShootPos = { CurPos.X, CurPos.Y + CurScale.hY() + 30.0f, 0.0f};
		float Deg = 0.0f;
		switch (Body->GetDir())
		{
		case EEngineDir::Left:
			ShootPos.X -= 60.0f;
			Deg = UEngineRandom::MainRandom.RandomFloat(140.0f, 170.0f);
			break;
		case EEngineDir::Right:
			ShootPos.X += 60.0f;
			Deg = UEngineRandom::MainRandom.RandomFloat(15.0f, 45.0f);
			break;
		}

		Deg *= UEngineMath::DToR;
		FVector ShootDir = { cosf(Deg), sinf(Deg), 0.0f };

		float ShootSpeed = UEngineRandom::MainRandom.RandomFloat(1200.0f, 1800.0f);

		PlayLevel->SetShootGrenade(ShootPos, ShootDir, ShootSpeed);
		IsGunShoot = true;
		--GunShootCount;
	}

	if (3 < Body->GetCurAnimationFrame() && 200 > Diff_X)
	{
		State.ChangeState(HeadHunterState::roll);
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		IsGunShoot = false;
		PatternOrder = 0;


		if (0 >= GunShootCount)
		{
			AdjustBodyPosByDir({ 12.0f, 0.0f, 0.0f });
			Body->ChangeAnimation(Anim::headhunter_putback_gun);
			PatternOrder = -1;
			return;
		}
	}
}

void AHeadHunterPhase2::SwordDashUpdate(float _DeltaTime)
{
	DashLaserAlpha += 5.0f * _DeltaTime;

	if (1.0f < DashLaserAlpha)
	{
		DashLaserAlpha = 1.0f;
	}

	DashLaser->SetMulColor({ 1.0f, 1.0f, 1.0f, DashLaserAlpha });

	if (true == Body->IsCurAnimationEnd())
	{
		Body->AnimationReset();
		Body->SetSprite(ImgRes::headhunter_dash);

		SetVelocityByDir({ 10000.0f, 0.0f, 0.0f });
		BodyCol->SetActive(false);
		DashLaser->SetActive(false);
		DashAttack->SetActive(true);
		PatternOrder = 1;
	}
}

void AHeadHunterPhase2::SwordDashUpdate1(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();

	// 속도 업데이트
	if (true == IsColWall(Dir))
	{
		Velocity = FVector::Zero;

		switch (Dir)
		{
		case EEngineDir::Left:
			while (true == IsColWall(Dir))
			{
				AddActorLocation({ 1.0f, 0.0f, 0.0f });
			}
			break;
		case EEngineDir::Right:
			while (true == IsColWall(Dir))
			{
				AddActorLocation({ -1.0f, 0.0f, 0.0f });
			}
			break;
		}
	
		Body->ChangeAnimation(Anim::headhunter_dashend);
		BodyCol->SetActive(true);
		DashAttack->SetActive(false);
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	DashAttack->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision>(_Other))
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			FVector AttackDir = { 0.0f, 0.0f, 0.0f };
			switch (Body->GetDir())
			{
			case EEngineDir::Left:
				AttackDir.X = -0.9f;
				break;
			case EEngineDir::Right:
				AttackDir.X = 0.9f;
				break;
			}

			Player->HitByEnemy(AttackDir);
		}
	);
}
