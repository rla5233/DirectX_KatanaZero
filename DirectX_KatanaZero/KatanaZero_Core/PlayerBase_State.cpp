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
	PosUpdate(_DeltaTime);

	IsDirChangeKeyDown();
	
	// StateChange Check
	if (true == IsRunInputStart())
	{
		State.ChangeState("IdleToRun");
		return;
	}

	if (true == IsRunInputPress())
	{
		State.ChangeState("IdleToRun");
		return;
	}

	if (true == IsCrouchInputStart())
	{
		State.ChangeState("PostCrouch");
		return;
	}

	if (true == IsJumpInputStart())
	{
		State.ChangeState("Jump");
		return;
	}
}

void APlayerBase::IdleToRunStart()
{
	SetRunAcc();
	Velocity = FVector::Zero;

	Renderer->ChangeAnimation(Anim::player_idle_to_run);
}

void APlayerBase::IdleToRun(float _DeltaTime)
{
	RunVelUpdate(_DeltaTime);
	PosUpdate(_DeltaTime);
	OnGroundPosUpdate();

	if (true == IsDirChangeKeyDown())
	{
		Velocity = FVector::Zero;
	}

	// StateChange Check
	if (true == IsAnykeyFree())
	{
		if (false == IsDirChangeKeyPress())
		{
			State.ChangeState("RunToIdle");
			return;
		}
	}

	if (true == IsJumpInputPress())
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsRunToRollInputStart())
	{
		State.ChangeState("Roll");
		return;
	}

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
	OnGroundPosUpdate();

	// StateChange Check
	if (true == IsJumpInputStart())
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == IsRunToRollInputStart())
	{
		State.ChangeState("Roll");
		return;
	}

	if (false == IsRunInputPress())
	{
		State.ChangeState("RunToIdle");
		return;
	}

	if (true == IsDirChangeKeyDown())
	{
		State.ChangeState("IdleToRun");
		return;
	}
}

void APlayerBase::RunToIdleStart()
{
	Renderer->ChangeAnimation(Anim::player_run_to_idle);	
}

void APlayerBase::RunToIdle(float _DeltaTime)
{
	if (true == IsDirChangeKeyDown())
	{
		Velocity = FVector::Zero;
	}

	// StateChange Check
	if (true == IsRunInputPress())
	{
		State.ChangeState("IdleToRun");
		return;
	}

	if (true == IsCrouchInputStart())
	{
		State.ChangeState("PostCrouch");
		return;
	}

	if (true == IsJumpInputStart())
	{
		State.ChangeState("Jump");
		return;
	}

	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayerBase::PostCrouchStart()
{
	Renderer->ChangeAnimation(Anim::player_postcrouch);
}

void APlayerBase::PostCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == IsCrouchToRollInputStart())
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
	Renderer->ChangeAnimation(Anim::player_roll);
}

void APlayerBase::Roll(float _DeltaTime)
{

	// StateChange Check


	if (true == Renderer->IsCurAnimationEnd())
	{
		if (true == IsRunInputPress())
		{
			State.ChangeState("Run");
			return;
		}

		State.ChangeState("Idle");
		return;
	}
}

void APlayerBase::JumpStart()
{
	IsGround = false;
	Velocity = { 0.0f, 400.0f, 0.0f };

	Renderer->ChangeAnimation(Anim::player_jump);
}

void APlayerBase::Jump(float _DeltaTime)
{
	IsDirChangeKeyDown();
	if (true == IsRunInputPress())
	{
		JumpVelUpdate(_DeltaTime);
	}

	PosUpdate(_DeltaTime);

	// StateChange Check
	if (false == IsJumpInputPress())
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
	IsDirChangeKeyDown();
	GravityUpdate(_DeltaTime);
	PosUpdate(_DeltaTime);

	// StateChange Check
	if (true == IsGround)
	{
		State.ChangeState("RunToIdle");
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
}