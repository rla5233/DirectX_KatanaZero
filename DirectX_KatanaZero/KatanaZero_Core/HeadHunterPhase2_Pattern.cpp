#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
#include "PlayerBase.h"

void AHeadHunterPhase2::PatternCheck()
{
}

// Pattern_Rifle1
void AHeadHunterPhase2::Rifle1LaserUpdate(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		SetRifle1LaserEffect();
		--Rifle1Count;
		PatternOrder = 1;
		UEngineSound::SoundPlay(SoundRes::hh_laser_lockon);
	}
}

void AHeadHunterPhase2::Rifle1LaserUpdate1(float _DeltaTime)
{
	FVector CurScale = AllRifleLaserEffect[RifleLaserIdx]->GetLocalScale();
	if (1280.0f < CurScale.X)
	{
		return;
	}

	float AddScaleX = 5000.0f * _DeltaTime;
	AllRifleLaserEffect[RifleLaserIdx]->AddScale({ AddScaleX, 0.0f, 0.0f });
	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		AllRifleLaserEffect[RifleLaserIdx]->AddPosition({ -AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	case EEngineDir::Right:
		AllRifleLaserEffect[RifleLaserIdx]->AddPosition({ AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	}
}

//void AHeadHunterPhase2::Rifle1LaserUpdate2(float _DeltaTime)
//{
//	LaserAlpha -= 9.0f * _DeltaTime;
//
//	if (0.0f > LaserAlpha)
//	{
//		LaserAlpha = 0.0f;
//		PatternOrder = -1;
//		LaserEffect->SetActive(false);
//		DelayCallBack(0.04f, [=]
//			{
//				if (HeadHunterState::pattern_rifle1 != State.GetCurStateName())
//				{
//					return;
//				}
//
//				LaserAlpha = 1.0f;
//				LaserEffect->SetActive(true);
//				LaserEffect->ChangeAnimation(Anim::effect_laser);
//				LaserEffect->AddScale({ 0.0f, 14.0f, 0.0f });
//				LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
//				switch (Body->GetDir())
//				{
//				case EEngineDir::Left:
//					LaserEffect->SetRotationDeg({ 0.0f, 180.0f, 0.0f });
//					break;
//				case EEngineDir::Right:
//					LaserEffect->SetRotationDeg({ 0.0f, 0.0f, 0.0f });
//					break;
//				}
//
//				LaserCol->SetActive(true);
//				USoundManager::SoundPlay_HH_LaserShot();
//
//				AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
//				PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);
//
//				DelayCallBack(0.1f, [=]
//					{
//						PatternOrder = 3;
//					}
//				);
//			}
//		);
//	}
//
//	LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
//}
//
//void AHeadHunterPhase2::Rifle1LaserUpdate3(float _DeltaTime)
//{
//	if (false == LaserEffect->IsActive())
//	{
//		return;
//	}
//
//	LaserColCheck();
//
//	float AddScaleY = -100.0f * _DeltaTime;
//	LaserEffect->AddScale({ 0.0f, AddScaleY, 0.0f });
//
//	FVector CurScale = LaserEffect->GetLocalScale();
//	if (0.0f > CurScale.Y)
//	{
//		LaserCol->SetActive(false);
//		LaserEffect->SetActive(false);
//
//		// 3회 발사후 돌아가기
//		if (0 == Rifle1Count)
//		{
//			Body->ChangeAnimation(Anim::headhunter_putback_rifle);
//			PatternOrder = -1;
//			return;
//		}
//
//		AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
//		FVector PlayerPos = PlayLevel->GetPlayerLocation();
//		FVector CurPos = GetActorLocation();
//		float DiffX = abs(CurPos.X - PlayerPos.X);
//		if (350.0f < DiffX)
//		{
//			DelayCallBack(0.06f, [=] { PatternOrder = 0; });
//		}
//		else
//		{
//			if (150.0f > DiffX)
//			{
//				State.ChangeState(HeadHunterState::roll);
//				return;
//			}
//
//			Body->ChangeAnimation(Anim::headhunter_putback_rifle);
//			PatternOrder = -1;
//			return;
//		}
//	}
//}

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

		SetAfterImagePlusColor({ 1.0f, 0.0f, 0.0f, 0.0f});
		SetAfterImageMulColor({ 1.0f, 0.1f, 0.1f, 0.3f});
		SetAfterImageDelayTime(0.0f);
		SetAfterImageTimeWeight(1.0f);
		SetAfterImageDelayTime(1.0f / 600000.0f);

		SetVelocityByDir({ 15000.0f, 0.0f, 0.0f });
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
		PatternOrder = 2;
	}

	// Effect
	CreateAfterImage(_DeltaTime);

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

			Player->HitByEnemy(AttackDir, EEnemyType::HeadHunterDash);
		}
	);
}

void AHeadHunterPhase2::SwordDashUpdate2(float _DeltaTime)
{
}
