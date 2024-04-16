#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase FSM

// 기본
void APlayerBase::IdleStart()
{
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_idle);
}
	
void APlayerBase::Idle(float _DeltaTime)
{
	// 방향 전환 체크
	IsDirChangeKeyDown();

	// 충돌 보정
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == IsRunInputDown())
	{
		if (false == IsColWall())
		{
			State.ChangeState("IdleToRun");
			return;
		}
	}

	if (true == IsCrouchInputPress())
	{
		if (true == IsRunInputPress())
		{
			State.ChangeState("IdleToRun");
			return;
		}

		State.ChangeState("PostCrouch");
		return;
	}

	if (true == IsJumpInputDown())
	{
		State.ChangeState("Jump");
		return;
	}

	if (false == IsOnGround() &&  false == IsOnPlatForm() 
	&&  false == IsOnStairs() &&  false == IsOnGP_Boundary())
	{
		State.ChangeState("Fall");
		return;
	}
}

// 기본에서 달리기
void APlayerBase::IdleToRunStart()
{
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_idle_to_run);
}

void APlayerBase::IdleToRun(float _DeltaTime)
{	
	// 속도 업데이트
	IdleToRunVelUpdate(_DeltaTime);

	if (true == IsDirChangeKeyDown())
	{
		Velocity = FVector::Zero;
	}

	if (true == IsColWall())
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
		State.ChangeState("Attack");
		return;
	}

	if (true == IsAnykeyFree())
	{
		State.ChangeState("RunToIdle");
		return;
	}

	if (true == IsRunToRollInputDown())
	{
		State.ChangeState("Roll");
		return;
	}

	if (true == IsJumpInputDown() && true == IsRunInputPress())
	{
		EEngineDir Dir = Renderer->GetDir();
		switch (Dir)
		{
		case EEngineDir::Left:
			Velocity.X = -Const::player_jump_start_speedx;
			break;
		case EEngineDir::Right:
			Velocity.X = Const::player_jump_start_speedx;
			break;
		}

		State.ChangeState("Jump");
		return;
	}

	if (true == Renderer->IsCurAnimationEnd() && true == IsRunInputPress())
	{
		State.ChangeState("Run");
		return;
	}
}

// 달리기
void APlayerBase::RunStart()
{
	SetMaxRunVel();

	Renderer->ChangeAnimation(Anim::player_run);
}

void APlayerBase::Run(float _DeltaTime)
{
	// 속도 업데이트
	DownStairGravityUpdate(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 보정
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == IsRunToRollInputDown())
	{
		State.ChangeState("Roll");
		return;
	}

	if (true == IsJumpInputDown())
	{
		State.ChangeState("Jump");
		return;
	}

	if (false == IsRunInputPress() || true == IsColWall())
	{
		if (true == true == IsColWall())
		{ 
			Velocity.X = 0.0f;
		}

		State.ChangeState("RunToIdle");
		return;
	}
}

// 달리기에서 기본으로
void APlayerBase::RunToIdleStart()
{
	Velocity.Y = 0.0f;

	Renderer->ChangeAnimation(Anim::player_run_to_idle);	
}

void APlayerBase::RunToIdle(float _DeltaTime)
{
	// 속도 업데이트
	RunToIdleVelUpdate(_DeltaTime);

	if (true == IsDirChangeKeyPress() || true == IsColWall())
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
		State.ChangeState("Attack");
		return;
	}

	if (true == IsRunInputPress() && false == IsColWall())
	{
		State.ChangeState("IdleToRun");
		return;
	}

	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

// 웅크리기
void APlayerBase::PostCrouchStart()
{
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_postcrouch);
}

void APlayerBase::PostCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (false == IsCrouchInputPress())
	{
		State.ChangeState("PreCrouch");
		return;
	}

	if (true == IsCrouchInputPress() && true == IsOnPlatForm())
	{
		State.ChangeState("Fall");
		return;
	}
	 
	if (true == IsCrouchToRollInputPress())
	{
		IsDirChangeKeyPress();
		State.ChangeState("Roll");
		return;
	}
}

// 웅크리기 해제
void APlayerBase::PreCrouchStart()
{
	Renderer->ChangeAnimation(Anim::player_precrouch);
}

void APlayerBase::PreCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

// 구르기
void APlayerBase::RollStart()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X = -1.0f * Const::player_roll_speedx;
		break;
	case EEngineDir::Right:
		Velocity.X = Const::player_roll_speedx;
		break;
	}	

	Renderer->ChangeAnimation(Anim::player_roll);
}

void APlayerBase::Roll(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColWall())
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

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		Velocity = FVector::Zero;
		State.ChangeState("Attack");
		return;
	}

	if (true == Renderer->IsCurAnimationEnd())
	{
		IsDirChangeKeyPress();

		if (true == IsRunInputPress())
		{
			State.ChangeState("Run");
			return;
		}
		
		if (true == IsCrouchInputPress())
		{
			State.ChangeState("PostCrouch");
			return;
		}
	
		State.ChangeState("Idle");
		return;
	}
}

// 점프
void APlayerBase::JumpStart()
{
	Velocity.Y = Const::player_jump_speedy;

	Renderer->ChangeAnimation(Anim::player_jump);
}

void APlayerBase::Jump(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColHeadToCeil())
	{
		Velocity.Y = 0.0f;
	}

	JumpGravityUpdate(_DeltaTime);

	if (true == IsRunInputPress())
	{
		JumpVelXUpdate(_DeltaTime);
	}

	if (true == IsDirChangeKeyDown() || true == IsColHeadToWall())
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
		State.ChangeState("Attack");
		return;
	}

	if (true == IsFallInputPress() ||  false == IsJumpInputPress() ||  0.0f > Velocity.Y)
	{
		State.ChangeState("Fall");
		return;
	}
}

void APlayerBase::FallStart()
{
	Renderer->ChangeAnimation(Anim::player_fall);
}

void APlayerBase::Fall(float _DeltaTime)
{
	// 속도 업데이트
	if (true == IsColHeadToCeil())
	{
		Velocity.Y = 0.0f;
	}

	if (true == IsFallInputPress())
	{
		Velocity.Y += Const::player_fall_input_accy * _DeltaTime;
	}

	FallGravityUpdate(_DeltaTime);
	
	if (true == IsDirChangeKeyDown() || true == IsColHeadToWall())
	{
		Velocity.X = 0.0f;
	}

	if (true == IsRunInputPress())
	{
		FallVelXUpdate(_DeltaTime);
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		Velocity.X = 0.0f;
		State.ChangeState("Attack");
		return;
	}

	if (true == IsOnPlatForm() && true == IsFallInputPress())
	{
		return;
	}

	if ((true == IsOnGround() || true == IsOnStairs() || true == IsOnGP_Boundary())
	&&  (true == IsRunToRollInputPress() && true == IsCrouchToRollInputPress()))
	{
		State.ChangeState("Roll");
		return;
	}

	if (true == IsOnGround() || true == IsOnPlatForm() 
	||  true == IsOnStairs() || true == IsOnGP_Boundary())
	{
		if (true == IsRunInputPress())
		{
			State.ChangeState("Run");
			return;
		}
		
		State.ChangeState("RunToIdle");
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
	SetAttackEffect(AttackDir);
	Renderer->ChangeAnimation(Anim::player_attack);
}

void APlayerBase::Attack(float _DeltaTime)
{
	FallGravityUpdate(_DeltaTime);

	if (true == IsColHeadToCeil())
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -10.0f, 0.0f });
	}
	else if (true == IsColHeadToWall())
	{
		Velocity.X = 0.0f;
	}

	if (true == IsOnGP_Boundary())
	{
		Velocity.Y = 0.0f;
	}

	if (true == IsOnStairs())
	{
		Velocity = FVector::Zero;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// StateChange Check
	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Fall");
		return;
	}
}


// State 초기화
void APlayerBase::StateInit()
{
	// State 생성
	State.CreateState("Idle");
	State.CreateState("IdleToRun");
	State.CreateState("Run");
	State.CreateState("RunToIdle");
	State.CreateState("PostCrouch");
	State.CreateState("PreCrouch");
	State.CreateState("Jump");
	State.CreateState("Fall");
	State.CreateState("Roll");
	State.CreateState("Attack");

	// State Start 함수 세팅
	State.SetStartFunction("Idle", std::bind(&APlayerBase::IdleStart, this));
	State.SetStartFunction("IdleToRun", std::bind(&APlayerBase::IdleToRunStart, this));
	State.SetStartFunction("Run", std::bind(&APlayerBase::RunStart, this));
	State.SetStartFunction("RunToIdle", std::bind(&APlayerBase::RunToIdleStart, this));
	State.SetStartFunction("PostCrouch", std::bind(&APlayerBase::PostCrouchStart, this));
	State.SetStartFunction("PreCrouch", std::bind(&APlayerBase::PreCrouchStart, this));
	State.SetStartFunction("Jump", std::bind(&APlayerBase::JumpStart, this));
	State.SetStartFunction("Fall", std::bind(&APlayerBase::FallStart, this));
	State.SetStartFunction("Roll", std::bind(&APlayerBase::RollStart, this));
	State.SetStartFunction("Attack", std::bind(&APlayerBase::AttackStart, this));

	// State Update 함수 세팅
	State.SetUpdateFunction("Idle", std::bind(&APlayerBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("IdleToRun", std::bind(&APlayerBase::IdleToRun, this, std::placeholders::_1));
	State.SetUpdateFunction("Run", std::bind(&APlayerBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction("RunToIdle", std::bind(&APlayerBase::RunToIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("PostCrouch", std::bind(&APlayerBase::PostCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction("PreCrouch", std::bind(&APlayerBase::PreCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction("Jump", std::bind(&APlayerBase::Jump, this, std::placeholders::_1));
	State.SetUpdateFunction("Fall", std::bind(&APlayerBase::Fall, this, std::placeholders::_1));
	State.SetUpdateFunction("Roll", std::bind(&APlayerBase::Roll, this, std::placeholders::_1));
	State.SetUpdateFunction("Attack", std::bind(&APlayerBase::Attack, this, std::placeholders::_1));
}