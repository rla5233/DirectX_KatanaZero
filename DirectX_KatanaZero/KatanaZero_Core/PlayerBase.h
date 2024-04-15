#pragma once
#include <EngineCore/StateManager.h>

// 설명 : Player 부모 클래스
class APlayerBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APlayerBase();
	~APlayerBase();

	// delete Function
	APlayerBase(const APlayerBase& _Other) = delete;
	APlayerBase(APlayerBase&& _Other) noexcept = delete;
	APlayerBase& operator=(const APlayerBase& _Other) = delete;
	APlayerBase& operator=(APlayerBase&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline USpriteRenderer* GetRenderer() const
	{
		return Renderer;
	}

	inline std::string GetCurState() const
	{
		return State.GetCurStateName();
	}

	bool IsOnGround();
	bool IsOnPlatForm();
	bool IsOnStairs();
	bool IsColWall();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void DefaultUpdate(float _DeltaTime);

	void AttackDelayTimeUpdate(float _DeltaTime);

private:
	bool IsDirChangeKeyDown();
	bool IsDirChangeKeyPress();
	void RendererDirChange(EEngineDir _Dir);

	void OnGroundPosAdjust();
	void OnStairPosAdjust();
	void OnPlatFormAdjust();

	void RollFallPosAdjust();

private:
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Back_Top = nullptr;
	USpriteRenderer* Back_Bot = nullptr;
	USpriteRenderer* Front_Top = nullptr;
	USpriteRenderer* Front_Bot = nullptr;

	FVector Top = { 30.0f, 65.0f, 0.0f };
	FVector Bot = { 30.0f, 0.0f, 0.0f };

	FVector Velocity = FVector::Zero;

	FVector AttackDir = FVector::Zero;
	float AttackDelayTimeCount = 0.0f;
	bool CanAttack = true;

// FSM
private:
	UStateManager State;
	void StateInit();

	void IdleStart();
	void Idle(float _DeltaTime);

	void IdleToRunStart();
	void IdleToRun(float _DeltaTime);

	void RunStart();
	void Run(float _DeltaTime);

	void RunToIdleStart();
	void RunToIdle(float _DeltaTime);

	void PostCrouchStart();
	void PostCrouch(float _DeltaTime);

	void PreCrouchStart();
	void PreCrouch(float _DeltaTime);

	void RollStart();
	void Roll(float _DeltaTime);

	void JumpStart();
	void Jump(float _DeltaTime);

	void FallStart();
	void Fall(float _DeltaTime);

	void AttackStart();
	void Attack(float _DeltaTime);

// FSM Input Check
private:
	bool IsRunInputDown();
	bool IsRunInputPress();

	bool IsCrouchInputDown();
	bool IsCrouchInputPress();

	bool IsRunToRollInputDown();
	bool IsRunToRollInputPress();

	bool IsCrouchToRollInputDown();
	bool IsCrouchToRollInputPress();

	bool IsJumpInputDown();
	bool IsJumpInputPress();

	bool IsFallInputPress();

	bool IsAttackInputDown();

// FSM Setting
private:
	void SetMaxRunVel();

	void SetAttackDir();

// FSM Update
private:
	void GravityUpdate(float _DeltaTime);

	void PosUpdate(float _DeltaTime);

	void IdleToRunVelUpdate(float _DeltaTime);

	void RunToIdleVelUpdate(float _DeltaTime);




	// 미 사용
	void RunGravityUpdate(float _DeltaTime);

	void JumpVelXUpdate(float _DeltaTime);
	void JumpVelYUpdate(float _DeltaTime);

	void RollVelXUpdate(float _DeltaTime);
	void RollVelYUpdate();

	void FallVelXUpdate(float _DeltaTime);
	void FallGravityUpdate(float _DeltaTime);
};

