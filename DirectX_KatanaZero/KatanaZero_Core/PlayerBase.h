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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool IsDirChangeKeyDown();
	bool IsDirChangeKeyPress();

private:
	USpriteRenderer* Renderer = nullptr;

	float MaxSpeed_X = 425.0f;
	float MaxSpeed_Y = 425.0f;
	FVector Velocity = FVector::Zero;
	FVector Acc = FVector::Zero;

	bool IsGround = true;

	float TimeCount = 0.0f;

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
	bool IsRunInputStart();
	bool IsRunInputPress();

	bool IsCrouchInputStart();
	bool IsCrouchInputPress();

	bool IsRunToRollInputStart();
	bool IsCrouchToRollInputStart();

	bool IsJumpInputStart();
	bool IsJumpInputPress();

// FSM Setting
private:
	void SetRunAcc();
	void SetRunVel();

// FSM Update
private:
	void PosUpdate(float _DeltaTime);

	void RunVelUpdate(float _DeltaTime);

	void JumpVelUpdate(float _DeltaTime);

	void GravityUpdate(float _DeltaTime);	
	void OnGroundPosUpdate();
};

