#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase FSM
void APlayerBase::IdleStart()
{
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_idle);
}

void APlayerBase::Idle(float _DeltaTime)
{
	// Check
	IsColWall();
	IsOnGround();

	IsDirChangeKeyDown();
	
	// StateChange Check
	//if (true == IsAttackInputDown() && true == CanAttack)
	//{
	//	State.ChangeState("Attack");
	//	return;
	//}

	if (true == IsRunInputDown())
	{
		if (false == IsColWall())
		{
			State.ChangeState("IdleToRun");
			return;
		}
	}

	//if (true == IsCrouchInputDown())
	//{
	//	State.ChangeState("PostCrouch");
	//	return;
	//}

	//if (true == IsJumpInputDown())
	//{
	//	State.ChangeState("Jump");
	//	return;
	//}
}

void APlayerBase::IdleToRunStart()
{
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_idle_to_run);
}

void APlayerBase::IdleToRun(float _DeltaTime)
{	

	// 기본 속도 업데이트
	RunVelUpdate(_DeltaTime);

	// 방향 체크
	if (true == IsDirChangeKeyDown())
	{
		Velocity = FVector::Zero;
	}

	// 벽 충돌 체크
	if (true == IsColWall())
	{
		Velocity.X = 0.0f;	
	}	

	// 위치 업데이트
	PosUpdate(_DeltaTime);
	
	IsOnGround();

	//OnStairPosAdjust();


	// StateChange Check
	if (true == IsAnykeyFree())
	{
		State.ChangeState("RunToIdle");
		return;
	}

	//if (true == IsJumpInputDown())
	//{
	//	State.ChangeState("Jump");
	//	return;
	//}

	//if (true == IsRunToRollInputDown())
	//{
	//	State.ChangeState("Roll");
	//	return;
	//}

	if (true == Renderer->IsCurAnimationEnd() && true == IsRunInputPress())
	{
		State.ChangeState("Run");
		return;
	}
}

void APlayerBase::RunStart()
{
	SetRunVel();

	Renderer->ChangeAnimation(Anim::player_run);
}

void APlayerBase::Run(float _DeltaTime)
{
	PosUpdate(_DeltaTime);
	//OnStairPosAdjust();

	//// StateChange Check
	//if (true == IsJumpInputDown())
	//{
	//	State.ChangeState("Jump");
	//	return;
	//}

	// RunToIdle 체크
	if (false == IsRunInputPress() || true == IsColWall())
	{
		if (true == true == IsColWall())
		{ 
			Velocity.X = 0.0f;
		}

		State.ChangeState("RunToIdle");
		return;
	}

	//if (true == IsRunToRollInputDown())
	//{
	//	if (true == IsOnPlatForm())
	//	{
	//		State.ChangeState("Fall");
	//		return;
	//	}

	//	State.ChangeState("PostCrouch");
	//	return;
	//}

	//if ())
	//{
	//	State.ChangeState("RunToIdle");
	//	return;
	//}

	//if (true == IsDirChangeKeyDown())
	//{
	//	State.ChangeState("IdleToRun");
	//	return;
	//}
}

void APlayerBase::RunToIdleStart()
{
	Velocity.Y = 0.0f;

	Renderer->ChangeAnimation(Anim::player_run_to_idle);	
}

void APlayerBase::RunToIdle(float _DeltaTime)
{


	if (true == IsDirChangeKeyPress() || true == IsColWall())
	{
		Velocity.X = 0.0f;
	}

	PosUpdate(_DeltaTime);



	// StateChange Check
	//if (true == IsRunInputPress())
	//{
	//	State.ChangeState("IdleToRun");
	//	return;
	//}

	//if (true == IsCrouchInputDown())
	//{
	//	State.ChangeState("PostCrouch");
	//	return;
	//}

	//if (true == IsJumpInputDown())
	//{
	//	State.ChangeState("Jump");
	//	return;
	//}

	//if (true == Renderer->IsCurAnimationEnd())
	//{
	//	State.ChangeState("Idle");
	//	return;
	//}
}

void APlayerBase::PostCrouchStart()
{
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_postcrouch);
}

void APlayerBase::PostCrouch(float _DeltaTime)
{
	GravityUpdate(_DeltaTime);



	PosUpdate(_DeltaTime);

	// StateChange Check
	if (true == IsCrouchToRollInputPress())
	{
		IsDirChangeKeyPress();
		State.ChangeState("Roll");
		return;
	}

	if (false == IsCrouchInputPress())
	{
		State.ChangeState("PreCrouch");
		return;
	}
	else
	{
		if (true == IsOnPlatForm())
		{
			AddActorLocation({ 0.0f, 2.0f, 0.0f });
			State.ChangeState("Fall");
			return;
		}
	}
}

void APlayerBase::PreCrouchStart()
{
	Renderer->ChangeAnimation(Anim::player_precrouch);
}

void APlayerBase::PreCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

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
	RollVelXUpdate(_DeltaTime);
	RollVelYUpdate();

	PosUpdate(_DeltaTime);
	RollFallPosAdjust();
	OnGroundPosAdjust();
	OnStairPosAdjust();

	// StateChange Check
	if (true == Renderer->IsCurAnimationEnd())
	{
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

void APlayerBase::JumpStart()
{
	AddActorLocation(FVector::Up);
	Velocity = Const::player_jump_vel;

	Renderer->ChangeAnimation(Anim::player_jump);
}

void APlayerBase::Jump(float _DeltaTime)
{
	JumpVelYUpdate(_DeltaTime);
	IsDirChangeKeyDown();

	if (true == IsRunInputPress())
	{
		JumpVelXUpdate(_DeltaTime);
	}

	PosUpdate(_DeltaTime);

	// StateChange Check
	if (true == IsFallInputPress() 
	||  false == IsJumpInputPress()
	||  0.0f > Velocity.Y)
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
	FallGravityUpdate(_DeltaTime);
	
	if (true == IsDirChangeKeyDown())
	{
		Velocity.X = 0.0f;
	}

	if (true == IsRunInputPress())
	{
		FallVelXUpdate(_DeltaTime);
	}

	if (true == IsFallInputPress())
	{
		Velocity.Y = -Const::player_fall_max_speedy;
	}

	PosUpdate(_DeltaTime);

	// StateChange Check
	if ((false == IsOnStairs() && false == IsOnGround()) 
	&&   true == IsFallInputPress())
	{
		return;
	}

	if (true == IsAttackInputDown() && true == CanAttack)
	{
		State.ChangeState("Attack");
		return;
	}

	if ((true == IsOnGround() || true == IsOnStairs() || true == IsOnStairs())
	&&   true == IsRunToRollInputPress() 
	&&   true == IsCrouchToRollInputPress())
	{
		State.ChangeState("Roll");
		return;
	}

	if (true == IsOnGround() || true == IsOnPlatForm() || true == IsOnStairs())
	{
		State.ChangeState("RunToIdle");
		return;
	}
}

void APlayerBase::AttackStart()
{
	SetAttackDir();
	AddActorLocation({ 0.0f, 10.0f, 0.0f });
	Velocity += AttackDir * 250.0f;

	AttackDelayTimeCount = Const::player_attack_delay;
	CanAttack = false;

	Renderer->ChangeAnimation(Anim::player_attack);
}

void APlayerBase::Attack(float _DeltaTime)
{
	PosUpdate(_DeltaTime);

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