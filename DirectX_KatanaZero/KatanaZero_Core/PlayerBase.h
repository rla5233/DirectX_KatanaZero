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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool IsDirChangeKeyDown();
	bool IsDirChangeKeyPress();
	bool IsOnGround();
	bool IsOnPlatForm();
	bool IsOnStairs();

	void OnStairPosAdjust();

private:
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Center = nullptr;

	FVector Velocity = FVector::Zero;

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

// FSM Setting
private:
	void SetRunVel();

// FSM Update
private:
	void GravityUpdate(float _DeltaTime);	
	void PosUpdate(float _DeltaTime);

	void RunVelUpdate(float _DeltaTime);

	void JumpVelXUpdate(float _DeltaTime);
	void JumpVelYUpdate(float _DeltaTime);

	void RollVelXUpdate(float _DeltaTime);

	void FallVelXUpdate(float _DeltaTime);
	void FallGravityUpdate(float _DeltaTime);
};

