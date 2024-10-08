#include "PreCompile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"
#include "MainCamera.h"
#include "HitLaser.h"

// State 초기화
void APlayerBase::StateInit()
{
	// State 생성
	State.CreateState(PlayerState::none);
	State.CreateState(PlayerState::idle);
	State.CreateState(PlayerState::idle_to_run);
	State.CreateState(PlayerState::run);
	State.CreateState(PlayerState::run_to_idle);
	State.CreateState(PlayerState::postcrouch);
	State.CreateState(PlayerState::precrouch);
	State.CreateState(PlayerState::jump);
	State.CreateState(PlayerState::fall);
	State.CreateState(PlayerState::roll);
	State.CreateState(PlayerState::attack);
	State.CreateState(PlayerState::wallslide);
	State.CreateState(PlayerState::flip);
	State.CreateState(PlayerState::kickdoor);
	State.CreateState(PlayerState::dead);
	State.CreateState(PlayerState::onlyfall);

	// State Start 함수 세팅
	State.SetStartFunction(PlayerState::none,			[=] {});
	State.SetStartFunction(PlayerState::idle,			std::bind(&APlayerBase::IdleStart, this));
	State.SetStartFunction(PlayerState::idle_to_run,	std::bind(&APlayerBase::IdleToRunStart, this));
	State.SetStartFunction(PlayerState::run,			std::bind(&APlayerBase::RunStart, this));
	State.SetStartFunction(PlayerState::run_to_idle,	std::bind(&APlayerBase::RunToIdleStart, this));
	State.SetStartFunction(PlayerState::postcrouch,		std::bind(&APlayerBase::PostCrouchStart, this));
	State.SetStartFunction(PlayerState::precrouch,		std::bind(&APlayerBase::PreCrouchStart, this));
	State.SetStartFunction(PlayerState::jump,			std::bind(&APlayerBase::JumpStart, this));
	State.SetStartFunction(PlayerState::fall,			std::bind(&APlayerBase::FallStart, this));
	State.SetStartFunction(PlayerState::roll,			std::bind(&APlayerBase::RollStart, this));
	State.SetStartFunction(PlayerState::attack,			std::bind(&APlayerBase::AttackStart, this));
	State.SetStartFunction(PlayerState::wallslide,		std::bind(&APlayerBase::WallSlideStart, this));
	State.SetStartFunction(PlayerState::flip,			std::bind(&APlayerBase::FlipStart, this));
	State.SetStartFunction(PlayerState::kickdoor,		std::bind(&APlayerBase::KickDoorStart, this));
	State.SetStartFunction(PlayerState::dead,			std::bind(&APlayerBase::DeadStart, this));
	State.SetStartFunction(PlayerState::onlyfall,		std::bind(&APlayerBase::OnlyFallStart, this));

	// State Update 함수 세팅
	State.SetUpdateFunction(PlayerState::none,			[=](float _DeltaTime) {});
	State.SetUpdateFunction(PlayerState::idle,			std::bind(&APlayerBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::idle_to_run,	std::bind(&APlayerBase::IdleToRun, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::run,			std::bind(&APlayerBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::run_to_idle,	std::bind(&APlayerBase::RunToIdle, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::postcrouch,	std::bind(&APlayerBase::PostCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::precrouch,		std::bind(&APlayerBase::PreCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::jump,			std::bind(&APlayerBase::Jump, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::fall,			std::bind(&APlayerBase::Fall, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::roll,			std::bind(&APlayerBase::Roll, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::attack,		std::bind(&APlayerBase::Attack, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::wallslide,		std::bind(&APlayerBase::WallSlide, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::flip,			std::bind(&APlayerBase::Flip, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::kickdoor,		std::bind(&APlayerBase::KickDoor, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::dead,			std::bind(&APlayerBase::Dead, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayerState::onlyfall,		std::bind(&APlayerBase::OnlyFall, this, std::placeholders::_1));

	// State End 함수 세팅
	State.SetEndFunction(PlayerState::attack,			[=] { AttackCol->SetActive(false); });
	State.SetEndFunction(PlayerState::roll,				[=] { IsInvincibleValue = false; });
	State.SetEndFunction(PlayerState::flip,				[=] { IsInvincibleValue = false; });
	State.SetEndFunction(PlayerState::kickdoor,			[=] { IsColDoorValue = false; });
	State.SetEndFunction(PlayerState::wallslide, [=]
		{
			Body->SetPosition({ 0.0f, 0.0f ,0.0f });
			USoundManager::GetInst().GetPlayerWallSlide().Off();
		}
	);
}

// 기본
void APlayerBase::IdleStart()
{
	Velocity = FVector::Zero;
}
	
void APlayerBase::Idle(float _DeltaTime)
{
	if (true == IsDoorKickInputPress())
	{
		State.ChangeState(PlayerState::kickdoor);
		return;
	}

	// 방향 전환 체크
	IsDirChangeKeyDown();

	// 충돌 보정
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	EEngineDir Dir = Body->GetDir();
	if (true == IsRunInputPress() && false == IsColDoorValue)
	{
		if (false == IsColWall(Dir))
		{
			State.ChangeState(PlayerState::idle_to_run);
			return;
		}
	}

	if (true == IsCrouchInputPress())
	{
		if (true == IsRunInputPress())
		{
			State.ChangeState(PlayerState::idle_to_run);
			return;
		}

		State.ChangeState(PlayerState::postcrouch);
		return;
	}

	if (true == IsJumpInputDown())
	{
		State.ChangeState(PlayerState::jump);
		return;
	}

	if (false == IsOnGround(Dir) && false == IsOnPlatForm(Dir) && false == IsOnCliff(Dir)
	&&  false == IsOnStairs(Dir) && false == IsOnGP_Boundary(Dir) && false == IsOnGroundBoundary(Dir))
	{
		State.ChangeState(PlayerState::fall);
		return;
	}
}

// 기본에서 달리기
void APlayerBase::IdleToRunStart()
{
	Velocity = FVector::Zero;
}

void APlayerBase::IdleToRun(float _DeltaTime)
{	
	// 속도 업데이트
	IdleToRunVelUpdate(_DeltaTime);

	if (true == IsDirChangeKeyDown())
	{
		Velocity = FVector::Zero;
	}

	EEngineDir Dir = Body->GetDir();
	if (true == IsColWall(Dir))
	{
		Velocity.X = 0.0f;	
	}	

	if (true == IsColDoorValue)
	{
		Velocity.X = 0.0f;
	}

	DownStairGravityUpdate(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);
	
	// 충돌 보정
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == IsRunToRollInputDown())
	{
		State.ChangeState(PlayerState::roll);
		return;
	}

	if (true == IsJumpInputDown() && true == IsRunInputPress())
	{
		EEngineDir Dir = Body->GetDir();
		switch (Dir)
		{
		case EEngineDir::Left:
			Velocity.X = -Const::player_jump_start_speedx;
			break;
		case EEngineDir::Right:
			Velocity.X = Const::player_jump_start_speedx;
			break;
		}

		State.ChangeState(PlayerState::jump);
		return;
	}

	if (true == Body->IsCurAnimationEnd() && true == IsRunInputPress())
	{
		State.ChangeState(PlayerState::run);
		return;
	}

	if (true == IsAnykeyFree()
	|| (false == IsRunInputPress() && true == IsAbilityInputPress()))
	{
		State.ChangeState(PlayerState::run_to_idle);
		return;
	}
}

// 달리기
void APlayerBase::RunStart()
{
	SetMaxRunVel();
	SetCroudEffect(5);
	SetAfterImageTimeWeight(14.0f);
	SetAfterImageMulColor({ 1.0f, 1.0f, 1.0f, 0.5f });
}

void APlayerBase::Run(float _DeltaTime)
{
	if (true == IsColDoorValue)
	{
		Velocity.X = 0;
		State.ChangeState(PlayerState::run_to_idle);
		return;
	}

	// 속도 업데이트
	DownStairGravityUpdate(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 보정
	ColCheckUpdate();

	// Effect
	CreateAfterImage(_DeltaTime);

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	// Collision Check
	if (true == IsRunToRollInputDown())
	{
		State.ChangeState(PlayerState::roll);
		return;
	}

	if (true == IsJumpInputDown())
	{
		State.ChangeState(PlayerState::jump);
		return;
	}

	EEngineDir Dir = Body->GetDir();
	if (false == IsRunInputPress() || true == IsColWall(Dir))
	{
		if (true == true == IsColWall(Dir))
		{ 
			Velocity.X = 0.0f;
		}

		State.ChangeState(PlayerState::run_to_idle);
		return;
	}
}

// 달리기에서 기본으로
void APlayerBase::RunToIdleStart()
{
	Velocity.Y = 0.0f;
}

void APlayerBase::RunToIdle(float _DeltaTime)
{
	// 속도 업데이트
	RunToIdleVelUpdate(_DeltaTime);

	EEngineDir Dir = Body->GetDir();
	if (true == IsDirChangeKeyPress() || true == IsColWall(Dir) || true == IsColDoorValue)
	{
		Velocity.X = 0.0f;
	}

	DownStairGravityUpdate(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// ColCheck
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == IsDoorKickInputPress())
	{
		State.ChangeState(PlayerState::kickdoor);
		return;
	}

	if (true == IsRunInputPress() && false == IsColWall(Dir) && false == IsColDoorValue)
	{
		State.ChangeState(PlayerState::idle_to_run);
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState(PlayerState::idle);
		return;
	}
}

// 웅크리기
void APlayerBase::PostCrouchStart()
{
	Velocity = FVector::Zero;
}

void APlayerBase::PostCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (false == IsCrouchInputPress())
	{
		State.ChangeState(PlayerState::precrouch);
		return;
	}

	if (true == IsCrouchInputPress() && true == IsOnPlatForm(Body->GetDir()))
	{
		State.ChangeState(PlayerState::fall);
		return;
	}
	 
	if (true == IsCrouchToRollInputPress())
	{
		IsDirChangeKeyPress();
		State.ChangeState(PlayerState::roll);
		return;
	}
}

// 웅크리기 해제
void APlayerBase::PreCrouchStart()
{
}

void APlayerBase::PreCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState(PlayerState::idle);
		return;
	}
}

// 구르기
void APlayerBase::RollStart()
{
	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X = -1.0f * Const::player_roll_speedx;
		break;
	case EEngineDir::Right:
		Velocity.X = Const::player_roll_speedx;
		break;
	}	

	SetAfterImageTimeWeight(7.0f);
	SetAfterImageMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	CroudTimeCount = Const::effect_roll_cloud_delay;
	IsInvincibleValue = true;
}

void APlayerBase::Roll(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	DownStairGravityUpdate(_DeltaTime);

	if (true == IsFallInputPress())
	{
		RollDownStairGravityUpdate(_DeltaTime);
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// ColCheck
	ColCheckUpdate();

	// 이펙트 생성
	CreateRollCroudEffect(_DeltaTime);
	CreateAfterImage(_DeltaTime);

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		Velocity = FVector::Zero;
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		IsDirChangeKeyPress();

		if (true == IsRunInputPress())
		{
			State.ChangeState(PlayerState::run);
			return;
		}
		
		if (true == IsCrouchInputPress())
		{
			State.ChangeState(PlayerState::postcrouch);
			return;
		}
	
		State.ChangeState(PlayerState::idle);
		return;
	}
}

// 점프
void APlayerBase::JumpStart()
{
	Velocity.Y = JumpSpeedWeight * Const::player_jump_speedy;
	SetAfterImageTimeWeight(5.0f);
	SetAfterImageMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });
	SetJumpEffect();
}

void APlayerBase::Jump(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColHeadToCeil(Body->GetDir()))
	{
		AddActorLocation({ 0.0f, -2.0f, 0.0f });
		Velocity.Y = 0.0f;
	}

	JumpGravityUpdate(_DeltaTime);

	if (true == IsRunInputPress())
	{
		JumpVelXUpdate(_DeltaTime);
	}

	if (true == IsDirChangeKeyDown() || true == IsColHeadToWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);
	
	// 충돌 체크
	ColCheckUpdate();

	// Effect
	if (75.0f < Velocity.Y)
	{
		CreateAfterImage(_DeltaTime);
	}

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == IsRunInputPress() && true == IsColWall(Body->GetDir()))
	{
		State.ChangeState(PlayerState::wallslide);
		return;
	}

	if (true == IsFallInputPress() ||  false == IsJumpInputPress() ||  0.0f > Velocity.Y)
	{
		State.ChangeState(PlayerState::fall);
		return;
	}
}

void APlayerBase::FallStart()
{
}

void APlayerBase::Fall(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColHeadToCeil(Body->GetDir()))
	{
		AddActorLocation({ 0.0f, -2.0f, 0.0f });
		Velocity.Y = 0.0f;
	}

	if (true == IsFallInputPress())
	{
		Velocity.Y += Const::player_fall_input_accy * _DeltaTime;
	}

	FallGravityUpdate(_DeltaTime);

	if (true == IsRunInputPress())
	{
		FallVelXUpdate(_DeltaTime);
	}

	if (true == IsDirChangeKeyDown() || true == IsColHeadToWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		Velocity.X = 0.0f;
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == IsOnPlatForm(Body->GetDir()) && true == IsFallInputPress())
	{
		return;
	}

	if (true == IsRunInputPress() && true == IsColWall(Body->GetDir()))
	{
		State.ChangeState(PlayerState::wallslide);
		return;
	}

	if ((true == IsOnGround(Body->GetDir()) || true == IsOnStairs(Body->GetDir()) || true == IsOnGP_Boundary(Body->GetDir()) || true == IsOnCliff(Body->GetDir()))
	&&  (true == IsRunToRollInputPress() && true == IsCrouchToRollInputPress()))
	{
		State.ChangeState(PlayerState::roll);
		return;
	}

	if (true == IsOnGround(Body->GetDir()) || true == IsOnPlatForm(Body->GetDir()) || true == IsOnCliff(Body->GetDir())
 	||  true == IsOnStairs(Body->GetDir()) || true == IsOnGP_Boundary(Body->GetDir()))
	{
		UEngineSound::SoundPlay(SoundRes::player_land).SetVolume(0.5f);

		SetLandEffect();
		if (true == IsRunInputPress())
		{
			State.ChangeState(PlayerState::run);
			return;
		}
		
		State.ChangeState(PlayerState::run_to_idle);
		return;
	}
}

void APlayerBase::AttackStart()
{
	// 방향 및 속도 설정
	SetAttackDir();
	AddActorLocation({ 0.0f, 10.0f, 0.0f });

	Velocity.X += AttackDir.X * 1000.0f;
	Velocity.Y += AttackDir.Y * 500.0f;

	if (2.0f * Const::player_max_speedx < Velocity.X)
	{
		Velocity.X = Const::player_max_speedx;
	}

	if ((-2.0f) *Const::player_max_speedx > Velocity.X)
	{
		Velocity.X = -Const::player_max_speedx;
	}

	// 지연 시간 설정
	AttackDelayTimeCount = Const::player_attack_delay;
	CanAttack = false;

	// 이펙트 설정
	SetAfterImageTimeWeight(6.0f);
	SetAfterImageMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });
	float Deg = UContentsMath::GetAngleToAxisX2D(AttackDir);
	SetAttackEffect(Deg);

	// 콜리전 설정
	AttackCol->SetPosition(AttackDir * 50.0f);
	AttackCol->AddPosition({ 0.0f, 30.0f, 0.0f });
	AttackCol->SetRotationDeg({ 0.0f, 0.0f, Deg });
	AttackCol->SetActive(true);
}

void APlayerBase::Attack(float _DeltaTime)
{
	// Collision Check
	AttackCollisionCheck();

	// 속도 업데이트
	FallGravityUpdate(_DeltaTime);

	if (4 < Body->GetCurAnimationFrame())
	{
		if (50.0f < abs(Velocity.X))
		{
			Velocity.X *= 0.99f;
		}
	}	

	if (true == IsColHeadToCeil(Body->GetDir()))
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -10.0f, 0.0f });
	}
	else if (true == IsColHeadToWall(Body->GetDir()) || true == IsColBotToWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	if (true == IsOnGP_Boundary(Body->GetDir()))
	{
		Velocity.Y = 0.0f;
	}

	if (true == IsOnStairs(Body->GetDir()))
	{
		Velocity = FVector::Zero;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// Effect
	CreateAfterImage(_DeltaTime);

	// StateChange Check
	if (true == Body->IsCurAnimationEnd())
	{
		Velocity.X *= 0.6f;
		State.ChangeState(PlayerState::fall);
		return;
	}
}

void APlayerBase::WallSlideStart()
{
	Velocity.X = 0.0f;
	Velocity.Y += 180.0f;

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetPosition({ -14.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ 14.0f, 0.0f, 0.0f });
		break;
	}

	CroudTimeCount = Const::effect_wallslide_cloud_delay;
}

void APlayerBase::WallSlide(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColHeadToCeil(Body->GetDir()))
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -2.0f, 0.0f });
		return;
	}

	WallGravityUpdate(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// 이펙트 생성
	if (100.0f < abs(Velocity.Y))
	{
		CreateWallSlideCroudEffect(_DeltaTime);
		USoundManager::GetInst().GetPlayerWallSlide().On();
	}
	else
	{
		USoundManager::GetInst().GetPlayerWallSlide().Off();
	}

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if (true == IsOnGround(Body->GetDir()) || true == IsOnPlatForm(Body->GetDir()) || true == IsOnGP_Boundary(Body->GetDir()))
	{
		State.ChangeState(PlayerState::idle);
		return;
	}

	if (false == IsColHeadToWall(Body->GetDir()) && false == IsColBotToWall(Body->GetDir()))
	{
		State.ChangeState(PlayerState::fall);
		return;
	}

	if (true == IsJumpInputDown())
	{
		// Effect Setting
		SetWallJumpEffet();
		EEngineDir Dir = Body->GetDir();
		switch (Dir)
		{
		case EEngineDir::Left:
			JumpLandEffect->SetRotationDeg({ 0.0f, 0.0f, -90.0f });
			JumpLandEffect->SetPosition(GetActorLocation() + FVector(21.0f, 52.0f, 0.0f));
			break;
		case EEngineDir::Right:
			JumpLandEffect->SetRotationDeg({ 0.0f, 0.0f, 90.0f });
			JumpLandEffect->SetPosition(GetActorLocation() + FVector(-21.0f, 52.0f, 0.0f));
			break;
		}		

		State.ChangeState(PlayerState::flip);
		return;
	}
}

void APlayerBase::FlipStart()
{
	EEngineDir CurDir = Body->GetDir();
	switch (CurDir)
	{
	case EEngineDir::Left:
		DirChange(EEngineDir::Right);
		Velocity.X = 1.5f * Const::player_max_speedx;
		break;
	case EEngineDir::Right:
		DirChange(EEngineDir::Left);
		Velocity.X = (-1.5f) * Const::player_max_speedx;
		break;
	}

	Velocity.Y = 600.0f;
	IsInvincibleValue = true;
	SetAfterImageTimeWeight(7.0f);
	SetAfterImageMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}

void APlayerBase::Flip(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColHeadToCeil(Body->GetDir()))
	{
		AddActorLocation({ 0.0f, -2.0f, 0.0f });
		Velocity.Y *= -1.0f;
	}

	GravityUpdate(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// Effect
	CreateAfterImage(_DeltaTime);

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState(PlayerState::attack);
		return;
	}

	if ((true == IsColWall(Body->GetDir()) || true == IsColHeadToWall(Body->GetDir()) || true == IsColBotToWall(Body->GetDir()))
	&&	(false == IsColHeadToCeil(Body->GetDir())))
	{
		Velocity.Y = 150.0f;
		State.ChangeState(PlayerState::wallslide);
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState(PlayerState::fall);
		return;
	}
}

void APlayerBase::DeadStart()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	EEngineDir Dir = Body->GetDir();

	Velocity = { 500.0f, 400.0f, 0.0f };
	switch (Dir)
	{
	case EEngineDir::Left:
		break;
	case EEngineDir::Right:
		Velocity.X *= -1.0f;
		break;
	}

	switch (HitEnemy)
	{
	case EEnemyType::Default:
		SetHitLaser(EHitLaserType::Default);
		break;
	case EEnemyType::Fan:
	case EEnemyType::CeilLaser:
		UEngineSound::SoundPlay(SoundRes::player_punch_hit).SetVolume(0.75f);
		UContentsHelper::ResetTimeScale();
		break;	
	case EEnemyType::CeilGun:
		Velocity.X = 0.0f;
		UContentsHelper::ResetTimeScale();
		break;
	case EEnemyType::TimeOut:
		Velocity.X = 0.0f;
		Velocity.Y = 0.0f;
		UContentsHelper::ResetTimeScale();
		break;
	case EEnemyType::HeadHunterLaser:
	{
		PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);
		UEngineSound::SoundPlay(SoundRes::player_punch_hit).SetVolume(0.75f);
		UContentsHelper::ResetTimeScale();
	}
		break;
	case EEnemyType::HeadHunterDash:
		PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);
		SetHitLaser(EHitLaserType::HeadHunterDash);
		break;
	}

	AddActorLocation({ 0.0f, 10.0f, 0.0f });

	FrontCol->SetActive(false);

	SetRecordingActive(false);
	PlayLevel->StateChange(PlayLevelState::player_dead);
	SubState.ChangeState(PlayerSubState::none);
	IsAbilityValue = false;

	InputOff();
}

void APlayerBase::Dead(float _DeltaTime)
{
	// 속도 업데이트
	GravityUpdate(_DeltaTime);

	EEngineDir Dir = Body->GetDir();
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir)
		|| true == IsOnGP_Boundary(Dir) || true == IsOnStairs(Dir))
	{
		Velocity = { 0.0f, 0.0f, 0.0f };
	}

	if (true == IsColWall(Dir) || true == IsColHeadToWall(Dir) || true == IsColBackToWall(Dir))
	{
		Velocity.X = 0.0f;
	}

	if (true == IsColHeadToCeil(Dir))
	{
		Velocity.Y *= -1.0f;
	}

	BodyCol->CollisionEnter(EColOrder::Door, [=](std::shared_ptr<UCollision> _Other)
		{
			Velocity.X = 0.0f;
		}
	);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	AbilityUpdate(_DeltaTime);
}

void APlayerBase::KickDoorStart()
{
}

void APlayerBase::KickDoor(float _DeltaTime)
{
}

void APlayerBase::OnlyFallStart()
{
}

void APlayerBase::OnlyFall(float _DeltaTime)
{
	// 속도 업데이트
	FallGravityUpdate(_DeltaTime);

	if (true == IsRunInputPress())
	{
		FallVelXUpdate(_DeltaTime);
	}

	if (true == IsDirChangeKeyDown() || true == IsColHeadToWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);
}

void APlayerBase::SetHitLaser(EHitLaserType _Type)
{
	Velocity *= 0.75f;
	DelayCallBack(0.105f, [=]
		{
			Velocity.X *= 4.0f;
		}
	);

	HitDir.Normalize2D();
	float Deg = UContentsMath::GetAngleToAxisX2D(HitDir);
	std::shared_ptr<AHitLaser> NewHitLaser = GetWorld()->SpawnActor<AHitLaser>("HitLaser");
	NewHitLaser->SetActorLocation(GetActorLocation() - (HitDir * 1000.0f) + FVector(0.0f, 40.0f, 0.0f));
	NewHitLaser->SetActorRotation({ 0.0f, 0.0f, Deg });
	NewHitLaser->SetVelocity(HitDir * 10000.0f);
	NewHitLaser->SetHitLaserType(_Type);
	UEngineSound::SoundPlay(SoundRes::player_punch_hit).SetVolume(0.75f);
}

void APlayerBase::HitByEnemy(FVector _HitDir, EEnemyType _EnemyType)
{
	if ((true == IsInvincibleValue && EEnemyType::Fan != _EnemyType) ||	 PlayerState::dead == State.GetCurStateName()
	||   true == IsCheatModeValue)
	{
		if (EEnemyType::TimeOut == _EnemyType)
		{
			HitEnemy = _EnemyType;
			HitDir = _HitDir;
			if (false == HitDir.IsZeroVector2D())
			{
				if (0.0f < HitDir.X)
				{
					Body->SetDir(EEngineDir::Left);
				}
				else
				{
					Body->SetDir(EEngineDir::Right);
				}
			}

			State.ChangeState(PlayerState::dead);
		}

		return;
	}

	HitEnemy = _EnemyType;
	HitDir = _HitDir;
	if (false == HitDir.IsZeroVector2D())
	{
		if (0.0f < HitDir.X)
		{
			Body->SetDir(EEngineDir::Left);
		}
		else
		{
			Body->SetDir(EEngineDir::Right);
		}
	}

	State.ChangeState(PlayerState::dead);
}