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
	if (true == IsRunInputStart())
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
	RunPosUpdate(_DeltaTime);

	if (true == IsAnykeyFree())
	{
		State.ChangeState("RunToIdle");
		return;
	}

	if (true == IsRunDirChange())
	{
		Velocity = FVector::Zero;
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
	RunPosUpdate(_DeltaTime);

	if (true == IsAnykeyFree())
	{
		State.ChangeState("RunToIdle");
		return;
	}

	if (true == IsRunDirChange())
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
	if (true == IsRunInputStart())
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

void APlayerBase::PostCrouchStart()
{
	Renderer->ChangeAnimation(Anim::player_postcrouch);
}

void APlayerBase::PostCrouch(float _DeltaTime)
{
	if (true == IsCrouchInputPressEnd())
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
	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayerBase::RollStart()
{

}

void APlayerBase::Roll(float _DeltaTime)
{

}

void APlayerBase::JumpStart()
{
	Renderer->ChangeAnimation(Anim::player_jump);
}

void APlayerBase::Jump(float _DeltaTime)
{
	GravityUpdate(_DeltaTime);

	if (true == IsGround)
	{
		State.ChangeState("Idle");
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

	// State Start 함수 세팅
	State.SetStartFunction("Idle", std::bind(&APlayerBase::IdleStart, this));
	State.SetStartFunction("IdleToRun", std::bind(&APlayerBase::IdleToRunStart, this));
	State.SetStartFunction("Run", std::bind(&APlayerBase::RunStart, this));
	State.SetStartFunction("RunToIdle", std::bind(&APlayerBase::RunToIdleStart, this));
	State.SetStartFunction("PostCrouch", std::bind(&APlayerBase::PostCrouchStart, this));
	State.SetStartFunction("PreCrouch", std::bind(&APlayerBase::PreCrouchStart, this));
	State.SetStartFunction("Jump", std::bind(&APlayerBase::JumpStart, this));

	// State Update 함수 세팅
	State.SetUpdateFunction("Idle", std::bind(&APlayerBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("IdleToRun", std::bind(&APlayerBase::IdleToRun, this, std::placeholders::_1));
	State.SetUpdateFunction("Run", std::bind(&APlayerBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction("RunToIdle", std::bind(&APlayerBase::RunToIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("PostCrouch", std::bind(&APlayerBase::PostCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction("PreCrouch", std::bind(&APlayerBase::PreCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction("Jump", std::bind(&APlayerBase::Jump, this, std::placeholders::_1));
}