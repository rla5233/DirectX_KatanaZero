#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"
#include "MainCamera.h"


void AHeadHunterPhase1::PatternCheck()
{
	AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	FVector CurPos = GetActorLocation();

	float DiffX = CurPos.X - PlayerPos.X;
	float LeftFirstPos = PlayLevel->GetRefPosX(HH_Phase1_RefPos::leftfirst);
	float LeftSecondPos = PlayLevel->GetRefPosX(HH_Phase1_RefPos::leftsecond);
	float RightSecondPos = PlayLevel->GetRefPosX(HH_Phase1_RefPos::rightsecond);
	float RightFirstPos = PlayLevel->GetRefPosX(HH_Phase1_RefPos::rightfirst);

	// Pattern Check

	// 중앙 위치 패턴
	if (LeftSecondPos < CurPos.X && RightSecondPos > CurPos.X)
	{
		if (150.0f >= abs(DiffX))
		{
			State.ChangeState(HeadHunterState::roll);
			
			// Reverse
			Velocity.X *= -1.0f;
			EEngineDir Dir = Body->GetDir();
			switch (Dir)
			{
			case EEngineDir::Left:
				Body->SetDir(EEngineDir::Right);
				break;
			case EEngineDir::Right:
				Body->SetDir(EEngineDir::Left);
				break;
			}

			return;
		}
		else
		{
			State.ChangeState(HeadHunterState::pattern_rifle1);
			return;
		}
	}


	// 플레이어와의 거리 계산 패턴
	if (500.0f < abs(DiffX))
	{
		State.ChangeState(HeadHunterState::pattern_rifle1);
		return;
	}
	
	if (500.0f >= abs(DiffX) && 90.0f < abs(DiffX))
	{
		if (LeftFirstPos > CurPos.X || RightFirstPos < CurPos.X)
		{
			State.ChangeState(HeadHunterState::roll);
			return;
		}
		else
		{
			int Prob = UEngineRandom::MainRandom.RandomInt(1, 100);

			if (2 <= RollCount || Prob <= 50)
			{
				State.ChangeState(HeadHunterState::pattern_airrifle1);
				return;
			}
			else
			{
				State.ChangeState(HeadHunterState::roll);
				return;
			}
		}
	}

	if (90.0f >= abs(DiffX))
	{
		if (LeftFirstPos <= CurPos.X && RightFirstPos >= CurPos.X)
		{
			int Prob = UEngineRandom::MainRandom.RandomInt(1, 100);

			if (2 <= RollCount || Prob <= 50)
			{
				State.ChangeState(HeadHunterState::pattern_airrifle1);
				return;
			}
			else
			{
				State.ChangeState(HeadHunterState::roll);
				return;
			}
		}

		State.ChangeState(HeadHunterState::roll);
		return;
	}
}

// Pattern_Rifle1
void AHeadHunterPhase1::Rifle1LaserUpdate(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		SetRifle1LaserEffect();
		--Pattern1Count;
		PatternOrder = 1;
	}
}

void AHeadHunterPhase1::Rifle1LaserUpdate1(float _DeltaTime)
{
	FVector CurScale = LaserEffect->GetLocalScale();
	if (1280.0f < CurScale.X)
	{
		return;
	}

	float AddScaleX = 5000.0f * _DeltaTime;
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

void AHeadHunterPhase1::Rifle1LaserUpdate2(float _DeltaTime)
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

	LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
}

void AHeadHunterPhase1::Rifle1LaserUpdate3(float _DeltaTime)
{
	if (false == LaserEffect->IsActive())
	{
		return;
	}

	LaserColCheck();

	float AddScaleY = -100.0f * _DeltaTime;
	LaserEffect->AddScale({ 0.0f, AddScaleY, 0.0f });

	FVector CurScale = LaserEffect->GetLocalScale();
	if (0.0f > CurScale.Y)
	{
		LaserCol->SetActive(false);
		LaserEffect->SetActive(false);

		// 3회 발사후 돌아가기
		if (0 == Pattern1Count)
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

// Pattern_AirRifle1
void AHeadHunterPhase1::AirRifle1Update(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
		float MidPosX = PlayLevel->GetRefPosX("Mid");
		float CurPosX = GetActorLocation().X;	

		// 속도 설정
		if (MidPosX < CurPosX)
		{
			Velocity = { 500.0f, 1000.0f, 0.0f };
		}
		else
		{
			Velocity = { -500.0f, 1000.0f, 0.0f };
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
		SetAfterImageAlphaWeight(0.6f);
		SetAfterImageTimeWeight(6.0f);

		PatternOrder = 1;
	}
}

void AHeadHunterPhase1::AirRifle1Update1(float _DeltaTime)
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

void AHeadHunterPhase1::AirRifle1Update2(float _DeltaTime)
{
	if (true == Body->IsCurAnimationEnd())
	{
		// 속도 공식 필요
		SetVelocityByDir({ 700.0f, 800.0f, 0.0f });

		Body->ChangeAnimation(Anim::headhunter_wall_jump);
		PatternOrder = 3;
	}
}

void AHeadHunterPhase1::AirRifle1Update3(float _DeltaTime)
{
	// 속도 업데이트
	ApplyGravity(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();
	LaserColCheck();

	// Effect
	CreateAfterImage(_DeltaTime);

	if (1 == Body->GetCurAnimationFrame())
	{
		SetAirRifle1LaserEffect();
	}
	else if (1 < Body->GetCurAnimationFrame() && 6 > Body->GetCurAnimationFrame())
	{
		AirRifle1LaserEffectUpdate(_DeltaTime);
	}
	else if (6 == Body->GetCurAnimationFrame())
	{
		LaserEffect->SetActive(false);
		LaserCol->SetActive(false);
	}

	if (true == IsOnGround(Body->GetDir()))
	{
		Body->ChangeAnimation(Anim::headhunter_land);
		PatternOrder = -1;
	}
}
