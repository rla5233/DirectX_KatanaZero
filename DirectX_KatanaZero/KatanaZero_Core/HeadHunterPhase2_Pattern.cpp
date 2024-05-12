#include "PreCompile.h"
#include "HeadHunterPhase2.h"

#include "HeadHunterLevel_Phase2.h"
#include "MainCamera.h"
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
	FVector CurScale = RifleLaserEffect->GetLocalScale();
	if (1280.0f < CurScale.X)
	{
		return;
	}

	float AddScaleX = 5000.0f * _DeltaTime;
	RifleLaserEffect->AddScale({ AddScaleX, 0.0f, 0.0f });
	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		RifleLaserEffect->AddPosition({ -AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	case EEngineDir::Right:
		RifleLaserEffect->AddPosition({ AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	}
}

void AHeadHunterPhase2::Rifle1LaserUpdate2(float _DeltaTime)
{
	RifleLaserAlpha -= 9.0f * _DeltaTime;

	if (0.0f > RifleLaserAlpha)
	{
		RifleLaserAlpha = 0.0f;
		PatternOrder = -1;
		RifleLaserEffect->SetActive(false);
		DelayCallBack(0.04f, [=]
			{
				if (HeadHunterState::pattern_rifle1 != State.GetCurStateName())
				{
					return;
				}

				RifleLaserAlpha = 1.0f;
				RifleLaserEffect->SetActive(true);
				RifleLaserEffect->ChangeAnimation(Anim::effect_laser);
				RifleLaserEffect->AddScale({ 0.0f, 14.0f, 0.0f });
				RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, RifleLaserAlpha });
				switch (Body->GetDir())
				{
				case EEngineDir::Left:
					RifleLaserEffect->SetRotationDeg({ 0.0f, 180.0f, 0.0f });
					break;
				case EEngineDir::Right:
					RifleLaserEffect->SetRotationDeg({ 0.0f, 0.0f, 0.0f });
					break;
				}

				RifleLaserCol->SetActive(true);
				USoundManager::SoundPlay_HH_LaserShot();

				AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
				PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);

				DelayCallBack(0.1f, [=]
					{
						PatternOrder = 3;
					}
				);
			}
		);
	}

	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, RifleLaserAlpha });
}

void AHeadHunterPhase2::Rifle1LaserUpdate3(float _DeltaTime)
{
	if (false == RifleLaserEffect->IsActive())
	{
		return;
	}

	RifleLaserColCheck();

	float AddScaleY = -100.0f * _DeltaTime;
	RifleLaserEffect->AddScale({ 0.0f, AddScaleY, 0.0f });

	FVector CurScale = RifleLaserEffect->GetLocalScale();
	if (0.0f > CurScale.Y)
	{
		RifleLaserCol->SetActive(false);
		RifleLaserEffect->SetActive(false);

		// 3회 발사후 돌아가기
		if (0 == Rifle1Count)
		{
			Body->ChangeAnimation(Anim::headhunter_putback_rifle);
			PatternOrder = -1;
			return;
		}

		AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
		FVector PlayerPos = PlayLevel->GetPlayerLocation();
		FVector CurPos = GetActorLocation();
		float DiffX = abs(CurPos.X - PlayerPos.X);
		if (350.0f < DiffX)
		{
			DelayCallBack(0.06f, [=] { PatternOrder = 0; });
		}
		else
		{
			if (150.0f > DiffX)
			{
				State.ChangeState(HeadHunterState::roll);
				return;
			}

			Body->ChangeAnimation(Anim::headhunter_putback_rifle);
			PatternOrder = -1;
			return;
		}
	}
}

// Pattern_GunShoot1
void AHeadHunterPhase2::GunShoot1Update(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		DelayCallBack(0.01f, [=]
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
		PlayLevel->GetKZMainCamera()->SetRetShakeRange({ -5.0f, 5.0f, -5.0f, 5.0f });
		PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);
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

// Pattern SwordDash
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
		SetAfterImageDelayTime(1.0f / 600000.0f);
		SetAfterImageTimeWeight(1.0f);

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
	
		AdjustBodyPosByDir({ 11.0f, 0.0f, 0.0f });
		Body->ChangeAnimation(Anim::headhunter_dashend);
		BodyCol->SetActive(true);
		DashAttack->SetActive(false);
		PatternOrder = -1;
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

// Pattern_AirRifle1
void AHeadHunterPhase2::AirRifle1Update(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
		float MidPosX = PlayLevel->GetRefPos(HH_Phase1_RefPos::mid);
		float CurPosX = GetActorLocation().X;

		// 속도 설정
		if (MidPosX < CurPosX)
		{
			Velocity = { 700.0f, 1000.0f, 0.0f };
		}
		else
		{
			Velocity = { -700.0f, 1000.0f, 0.0f };
		}

		// 위치 설정
		AddActorLocation({ 0.0f, 2.0f, 0.0f });

		// 렌더러 설정
		if (0.0f < Velocity.X)
		{
			Body->SetDir(EEngineDir::Left);
		}
		else
		{
			Body->SetDir(EEngineDir::Right);
		}

		Body->SetPosition(FVector::Zero);
		Body->ChangeAnimation(Anim::headhunter_jump);

		SetAfterImagePlusColor({ 1.0f, 0.0f, 1.0f });
		SetAfterImageMulColor({ 1.0f, 1.0f, 1.0f, 0.4f });
		SetAfterImageDelayTime(1.0f / 60.0f);
		SetAfterImageTimeWeight(6.0f);

		PatternOrder = 1;
	}
}

void AHeadHunterPhase2::AirRifle1Update1(float _DeltaTime)
{
	// 속도 업데이트
	ApplyGravity(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// Effect
	CreateAfterImage(_DeltaTime);

	// State Check
	if (true == IsColBackToWall(Body->GetDir()))
	{
		Body->ChangeAnimation(Anim::headhunter_wall_idle);
		Velocity = FVector::Zero;
		PatternOrder = 2;
		return;
	}

	if (true == IsOnGround(Body->GetDir()))
	{
		State.ChangeState(HeadHunterState::idle);
		PatternOrder = -1;
		return;
	}
}

void AHeadHunterPhase2::AirRifle1Update2(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		// 속도 공식 필요
		EEngineDir Dir = Body->GetDir();
		switch (Dir)
		{
		case EEngineDir::Left:
			AirRifle1FirstDeg = 180.0f;
			AirRifle1DegCount = AirRifle1FirstDeg;
			AirRifle1DegInter = 10.0f;
			Velocity = { -700.0f, 800.0f, 0.0f };
			break;
		case EEngineDir::Right:
			AirRifle1FirstDeg = 0.0f;
			AirRifle1DegCount = AirRifle1FirstDeg;
			AirRifle1DegInter = -10.0f;
			Velocity = { 700.0f, 800.0f, 0.0f };
			break;
		}

		Body->ChangeAnimation(Anim::headhunter_wall_jump);
		AirRifle1ShootCount = 0;
		IsAirRifleShake = false;
		PatternOrder = 3;
	}
}

void AHeadHunterPhase2::AirRifle1Update3(float _DeltaTime)
{
	// 속도 업데이트
	ApplyGravity(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// Effect
	CreateAfterImage(_DeltaTime);

	if (1 <= Body->GetCurAnimationFrame() && 18 > AirRifle1ShootCount)
	{
		switch (Body->GetDir())
		{
		case EEngineDir::Left:
			AirRifle1DegCount += 375.0f * _DeltaTime;
			if (AirRifle1FirstDeg + AirRifle1ShootCount * AirRifle1DegInter < AirRifle1DegCount)
			{
				AirRifle1DegCount = AirRifle1FirstDeg + AirRifle1ShootCount * AirRifle1DegInter;
				SetAirRifle1Effect();
			}
			break;		
		case EEngineDir::Right:
			AirRifle1DegCount -= 375.0f * _DeltaTime;
			if (AirRifle1FirstDeg + AirRifle1ShootCount * AirRifle1DegInter > AirRifle1DegCount)
			{
				AllSparkEffect[SparkIdx]->SetPosition(GetActorLocation());
				AirRifle1DegCount = AirRifle1FirstDeg + AirRifle1ShootCount * AirRifle1DegInter;
				SetAirRifle1Effect();
			}
			break;
		}
	}

	// State Check
	if (true == IsOnGround(Body->GetDir()))
	{
		Body->ChangeAnimation(Anim::headhunter_land);
		PatternOrder = -1;
	}
}

// Pattern AirRifle2
void AHeadHunterPhase2::AirRifle2Update(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		SetAirRifle2Effect();
		DelayCallBack(0.25f, [=] { PatternOrder = 1; });
		PatternOrder = -1;
	}
}

void AHeadHunterPhase2::AirRifle2Update1(float _DeltaTime)
{
	RifleLaserAlpha -= 8.0f * _DeltaTime;
	
	if (0.0f > RifleLaserAlpha)
	{
		RifleLaserAlpha = 0.0f;
		DelayCallBack(0.05f, [=] 
			{ 
				SetAirRifle2Effect1();
				RifleLaserCol->SetActive(true);
				Body->ChangeAnimation(Anim::headhunter_sweep);
				PatternOrder = 2; 
			}
		);
		PatternOrder = -1;
	}

	RifleLaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, RifleLaserAlpha });
}

void AHeadHunterPhase2::AirRifle2Update2(float _DeltaTime)
{
	AirRifle2TimeCount += 1.22f  * _DeltaTime;
	float Deg = UContentsMath::LerpClampf(360.0f, 180.0f, AirRifle2TimeCount);
	RifleLaserEffect->SetRotationDeg({ 0.0f, 0.0f, Deg });
	float Rad = Deg * UEngineMath::DToR;
	RifleLaserEffect->SetPosition({ 690.0f * cosf(Rad), 690.0f * sinf(Rad) + 56.0f, 0.0f });

	RifleLaserCol->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision> _Other)
		{
			APlayerBase* Player =dynamic_cast<APlayerBase*>(_Other->GetActor());
			Player->HitByEnemy({ cosf(Rad), sinf(Rad), 0.0f }, EEnemyType::HeadHunterLaser);
		}
	);

	if (15 < Body->GetCurAnimationFrame())
	{
		RifleLaserEffect->AddScale({ 0.0f, -180.0f *_DeltaTime, 0.0f });

		float ScaleY = RifleLaserEffect->GetLocalScale().Y;
		if (0.0f > ScaleY)
		{
			RifleLaserEffect->SetScale(FVector::Zero);
		}
	}

	if (true == Body->IsCurAnimationEnd())
	{ 
		RifleLaserEffect->SetActive(false);
		RifleLaserCol->SetActive(false);

		Body->AnimationReset();
		Body->SetSprite(ImgRes::headhunter_dash);
		Body->SetDir(EEngineDir::Left);
		Body->SetRotationDeg({ 0.0f, 0.0f, 90.0f });
		

		SetAfterImagePlusColor({ 1.0f, 0.0f, 0.0f, 0.0f });
		SetAfterImageMulColor({ 1.0f, 0.1f, 0.1f, 0.3f });
		SetAfterImageDelayTime(1.0f / 600000.0f);
		SetAfterImageTimeWeight(1.0f);
		Velocity = { 0.0f, -15000.0f, 0.0f };
		DashAttack->SetActive(true);
		PatternOrder = 3;
	}
}

void AHeadHunterPhase2::AirRifle2Update3(float _DeltaTime)
{
	// ColCheck
	EEngineDir Dir = Body->GetDir();
	if (true == IsOnGround(Dir))
	{
		OnGroundPosAdjust(Dir);
		Velocity = FVector::Zero;
		BodyCol->SetActive(true);
		DashAttack->SetActive(false);
		Body->ChangeAnimation(Anim::headhunter_dashend);
		Body->SetRotationDeg(FVector::Zero);
		Body->SetPosition({ -18.0f, 0.0f, 0.0f });
		PatternOrder = -1;
	}
	
	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// Effect
	CreateAfterImage(_DeltaTime);

	DashAttack->CollisionEnter(EColOrder::PlayerBody, [=](std::shared_ptr<UCollision>(_Other))
		{
			APlayerBase* Player = dynamic_cast<APlayerBase*>(_Other->GetActor());
			FVector PlayerPos = Player->GetActorLocation();
			FVector CurPos = GetActorLocation();

			FVector AttackDir = { 0.0f, 0.0f, 0.0f };
			if (CurPos.X < PlayerPos.X)
			{
				AttackDir.X = 0.9f;
			}
			else
			{
				AttackDir.X = -0.9f;
			}

			Player->HitByEnemy(AttackDir, EEnemyType::HeadHunterDash);
		}
	);
}

// Pattern Complex
void AHeadHunterPhase2::ComplexUpdate(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		Body->ChangeAnimation(Anim::headhunter_tel_out);
		PatternOrder = 1;
		++AirLaserCount;

		if (AirPosX.size() <= AirLaserCount)
		{
			PatternOrder = 2;
		}
	}
}

void AHeadHunterPhase2::ComplexUpdate1(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		SetActorLocation({ AirPosX[AirLaserCount], AirPosY, 0.0f });
		Body->ChangeAnimation(Anim::headhunter_tel_in);
		PatternOrder = 0;
	}
}

void AHeadHunterPhase2::ComplexUpdate2(float _DeltaTime)
{
	
}

void AHeadHunterPhase2::ComplexUpdate3(float _DeltaTime)
{

}

void AHeadHunterPhase2::ComplexUpdate4(float _DeltaTime)
{
}
