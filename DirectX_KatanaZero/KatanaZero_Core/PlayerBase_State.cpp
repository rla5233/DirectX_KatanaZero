#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase FSM

// �⺻
void APlayerBase::IdleStart()
{
	Velocity = FVector::Zero;

	Body->ChangeAnimation(Anim::player_idle);
}
	
void APlayerBase::Idle(float _DeltaTime)
{
	if (true == IsDoorKickInputPress())
	{
		State.ChangeState("KickDoor");
		return;
	}

	// ���� ��ȯ üũ
	IsDirChangeKeyDown();

	// �浹 ����
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	EEngineDir Dir = Body->GetDir();
	if (true == IsRunInputPress() && false == IsColDoorValue)
	{
		if (false == IsColWall(Dir))
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

	if (false == IsOnGround(Dir) && false == IsOnPlatForm(Dir)
	&&  false == IsOnStairs(Dir) && false == IsOnGP_Boundary(Dir))
	{
		State.ChangeState("Fall");
		return;
	}
}

// �⺻���� �޸���
void APlayerBase::IdleToRunStart()
{
	Velocity = FVector::Zero;

	Body->ChangeAnimation(Anim::player_idle_to_run);
}

void APlayerBase::IdleToRun(float _DeltaTime)
{	
	// �ӵ� ������Ʈ
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

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);
	
	// �浹 ����
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

		State.ChangeState("Jump");
		return;
	}

	if (true == Body->IsCurAnimationEnd() && true == IsRunInputPress())
	{
		State.ChangeState("Run");
		return;
	}
}

// �޸���
void APlayerBase::RunStart()
{
	SetMaxRunVel();

	Body->ChangeAnimation(Anim::player_run);
	SetCroudEffect(5);
}

void APlayerBase::Run(float _DeltaTime)
{
	if (true == IsColDoorValue)
	{
		Velocity.X = 0;
		State.ChangeState("RunToIdle");
		return;
	}

	// �ӵ� ������Ʈ
	DownStairGravityUpdate(_DeltaTime);

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// �浹 ����
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	// Collision Check
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

	EEngineDir Dir = Body->GetDir();
	if (false == IsRunInputPress() || true == IsColWall(Dir))
	{
		if (true == true == IsColWall(Dir))
		{ 
			Velocity.X = 0.0f;
		}

		State.ChangeState("RunToIdle");
		return;
	}
}

// �޸��⿡�� �⺻����
void APlayerBase::RunToIdleStart()
{
	Velocity.Y = 0.0f;

	Body->ChangeAnimation(Anim::player_run_to_idle);
}

void APlayerBase::RunToIdle(float _DeltaTime)
{
	// �ӵ� ������Ʈ
	RunToIdleVelUpdate(_DeltaTime);

	EEngineDir Dir = Body->GetDir();
	if (true == IsDirChangeKeyPress() || true == IsColWall(Dir) || true == IsColDoorValue)
	{
		Velocity.X = 0.0f;
	}

	DownStairGravityUpdate(_DeltaTime);

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// ColCheck
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == IsDoorKickInputPress())
	{
		State.ChangeState("KickDoor");
		return;
	}

	if (true == IsRunInputPress() && false == IsColWall(Dir) && false == IsColDoorValue)
	{
		State.ChangeState("IdleToRun");
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

// ��ũ����
void APlayerBase::PostCrouchStart()
{
	Velocity = FVector::Zero;

	Body->ChangeAnimation(Anim::player_postcrouch);
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

	if (true == IsCrouchInputPress() && true == IsOnPlatForm(Body->GetDir()))
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

// ��ũ���� ����
void APlayerBase::PreCrouchStart()
{
	Body->ChangeAnimation(Anim::player_precrouch);
}

void APlayerBase::PreCrouch(float _DeltaTime)
{
	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

// ������
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

	Body->ChangeAnimation(Anim::player_roll);
	CroudTimeCount = Const::effect_cloud_delay;
}

void APlayerBase::Roll(float _DeltaTime)
{
	// �ӵ� ������Ʈ
	if (true == IsColWall(Body->GetDir()))
	{
		Velocity.X = 0.0f;
	}

	DownStairGravityUpdate(_DeltaTime);

	if (true == IsFallInputPress())
	{
		RollDownStairGravityUpdate(_DeltaTime);
	}

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// ColCheck
	ColCheckUpdate();

	// ����Ʈ ����
	CreateRollCroudEffect(_DeltaTime);

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		Velocity = FVector::Zero;
		State.ChangeState("Attack");
		return;
	}

	if (true == Body->IsCurAnimationEnd())
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

// ����
void APlayerBase::JumpStart()
{
	Velocity.Y = Const::player_jump_speedy;

	Body->ChangeAnimation(Anim::player_jump);
	SetJumpEffect();
}

void APlayerBase::Jump(float _DeltaTime)
{
	// �ӵ� ������Ʈ
	if (true == IsColHeadToCeil(Body->GetDir()))
	{
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

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);
	
	// �浹 üũ
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == IsRunInputPress() && true == IsColWall(Body->GetDir()))
	{
		State.ChangeState("WallSlide");
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
	Body->ChangeAnimation(Anim::player_fall);
}

void APlayerBase::Fall(float _DeltaTime)
{
	// �ӵ� ������Ʈ
	if (true == IsColHeadToCeil(Body->GetDir()))
	{
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

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// �浹 üũ
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		Velocity.X = 0.0f;
		State.ChangeState("Attack");
		return;
	}

	if (true == IsOnPlatForm(Body->GetDir()) && true == IsFallInputPress())
	{
		return;
	}

	if (true == IsRunInputPress() && true == IsColWall(Body->GetDir()))
	{
		State.ChangeState("WallSlide");
		return;
	}

	if ((true == IsOnGround(Body->GetDir()) || true == IsOnStairs(Body->GetDir()) || true == IsOnGP_Boundary(Body->GetDir()))
	&&  (true == IsRunToRollInputPress() && true == IsCrouchToRollInputPress()))
	{
		State.ChangeState("Roll");
		return;
	}

	if (true == IsOnGround(Body->GetDir()) || true == IsOnPlatForm(Body->GetDir())
 	||  true == IsOnStairs(Body->GetDir()) || true == IsOnGP_Boundary(Body->GetDir()))
	{
		SetLandEffect();
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
	// ���� �� �ӵ� ����
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

	// ���� �ð� ����
	AttackDelayTimeCount = Const::player_attack_delay;
	CanAttack = false;

	// ����Ʈ ����
	float Deg = UContentsMath::GetAngleToX_2D(AttackDir);
	SetAttackEffect(Deg);
	Body->ChangeAnimation(Anim::player_attack);

	// �ݸ��� ����
	AttackCol->SetPosition(AttackDir * 75.0f);
	AttackCol->AddPosition({ 0.0f, 40.0f, 0.0f });
	AttackCol->SetRotationDeg({ 0.0f, 0.0f, Deg });
	AttackCol->SetActive(true);
}

void APlayerBase::Attack(float _DeltaTime)
{
	// Collision Check
	AttackCollisionCheck();

	FallGravityUpdate(_DeltaTime);

	if (true == IsColHeadToCeil(Body->GetDir()))
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -10.0f, 0.0f });
	}
	else if (true == IsColHeadToWall(Body->GetDir()))
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

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// �浹 üũ
	ColCheckUpdate();

	// StateChange Check
	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState("Fall");
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
		Body->SetPosition({ -9.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ 9.0f, 0.0f, 0.0f });
		break;
	}

	Body->ChangeAnimation(ImgRes::player_wall_slide);
}

void APlayerBase::WallSlide(float _DeltaTime)
{
	// �ӵ� ������Ʈ
	WallGravityUpdate(_DeltaTime);

	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// �浹 üũ
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == IsOnGround(Body->GetDir()) || true == IsOnPlatForm(Body->GetDir()))
	{
		State.ChangeState("Idle");
		return;
	}

	if (true == IsJumpInputDown())
	{
		State.ChangeState("Flip");
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

	Velocity.Y = 500.0f;

	Body->ChangeAnimation(Anim::player_flip);
}

void APlayerBase::Flip(float _DeltaTime)
{
	// ��ġ ������Ʈ
	PosUpdate(_DeltaTime);

	// �浹 üũ
	ColCheckUpdate();

	// StateChange Check
	if (true == IsAttackInputDown())
	{
		State.ChangeState("Attack");
		return;
	}

	if (true == IsColWall(Body->GetDir()) || true == IsColHeadToWall(Body->GetDir()))
	{
		State.ChangeState("WallSlide");
		return;
	}

	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState("Fall");
		return;
	}
}

void APlayerBase::ReplayStart()
{
	IsPlayValue = false;
	SetReplayStart();
}

void APlayerBase::Replay(float _DeltaTime)
{
	Replaying(_DeltaTime);
}

// State �ʱ�ȭ
void APlayerBase::StateInit()
{
	// State ����
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
	State.CreateState("WallSlide");
	State.CreateState("Flip");
	State.CreateState("KickDoor");
	State.CreateState("Replay");

	// State Start �Լ� ����
	State.SetStartFunction("Idle",			std::bind(&APlayerBase::IdleStart, this));
	State.SetStartFunction("IdleToRun",		std::bind(&APlayerBase::IdleToRunStart, this));
	State.SetStartFunction("Run",			std::bind(&APlayerBase::RunStart, this));
	State.SetStartFunction("RunToIdle",		std::bind(&APlayerBase::RunToIdleStart, this));
	State.SetStartFunction("PostCrouch",	std::bind(&APlayerBase::PostCrouchStart, this));
	State.SetStartFunction("PreCrouch",		std::bind(&APlayerBase::PreCrouchStart, this));
	State.SetStartFunction("Jump",			std::bind(&APlayerBase::JumpStart, this));
	State.SetStartFunction("Fall",			std::bind(&APlayerBase::FallStart, this));
	State.SetStartFunction("Roll",			std::bind(&APlayerBase::RollStart, this));
	State.SetStartFunction("Attack",		std::bind(&APlayerBase::AttackStart, this));
	State.SetStartFunction("WallSlide",		std::bind(&APlayerBase::WallSlideStart, this));
	State.SetStartFunction("Flip",			std::bind(&APlayerBase::FlipStart, this));
	State.SetStartFunction("KickDoor",		[=] { Body->ChangeAnimation(Anim::player_kick_door);	});
	State.SetStartFunction("Replay",		std::bind(&APlayerBase::ReplayStart, this));

	// State Update �Լ� ����
	State.SetUpdateFunction("Idle",			std::bind(&APlayerBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("IdleToRun",	std::bind(&APlayerBase::IdleToRun, this, std::placeholders::_1));
	State.SetUpdateFunction("Run",			std::bind(&APlayerBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction("RunToIdle",	std::bind(&APlayerBase::RunToIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("PostCrouch",	std::bind(&APlayerBase::PostCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction("PreCrouch",	std::bind(&APlayerBase::PreCrouch, this, std::placeholders::_1));
	State.SetUpdateFunction("Jump",			std::bind(&APlayerBase::Jump, this, std::placeholders::_1));
	State.SetUpdateFunction("Fall",			std::bind(&APlayerBase::Fall, this, std::placeholders::_1));
	State.SetUpdateFunction("Roll",			std::bind(&APlayerBase::Roll, this, std::placeholders::_1));
	State.SetUpdateFunction("Attack",		std::bind(&APlayerBase::Attack, this, std::placeholders::_1));
	State.SetUpdateFunction("WallSlide",	std::bind(&APlayerBase::WallSlide, this, std::placeholders::_1));
	State.SetUpdateFunction("Flip",			std::bind(&APlayerBase::Flip, this, std::placeholders::_1));
	State.SetUpdateFunction("KickDoor",		[=] (float _DeltaTime){ });
	State.SetUpdateFunction("Replay",		std::bind(&APlayerBase::Replay, this, std::placeholders::_1));

	// State End �Լ� ����
	State.SetEndFunction("Attack",			[=] { AttackCol->SetActive(false); });
	State.SetEndFunction("WallSlide",		[=] {	Body->SetPosition({ 0.0f, 0.0f ,0.0f }); });
	State.SetEndFunction("Flip",			[=] { Velocity.Y = 0.0f; });
	State.SetEndFunction("KickDoor",		[=] { IsColDoorValue = false; });
}