#pragma once
#include <EngineCore/StateManager.h>
#include "RecordingObject.h"

// 설명 : Player 부모 클래스
class APlayerBase : public AActor, public URecordingObject
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

	inline bool IsStairUp() const
	{
		return IsStairsUpValue;
	}

	// 체크 함수
	bool IsOnGround();
	bool IsOnPlatForm();
	bool IsOnGP_Boundary();
	bool IsOnStairs();
	bool IsColWall();
	bool IsColHeadToWall();
	bool IsColHeadToCeil();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 기본 업데이트 함수
	void DefaultUpdate(float _DeltaTime);

	void AttackDelayTimeUpdate(float _DeltaTime);

private:
	// 방향 관련
	bool IsDirChangeKeyDown();
	bool IsDirChangeKeyPress();
	void RendererDirChange(EEngineDir _Dir);

	// 위치 조정
	void OnGroundPosAdjust();
	void UpStairPosAdjust();

private:
	USpriteRenderer* Renderer = nullptr;

	USpriteRenderer* Back_Top = nullptr;
	USpriteRenderer* Back_Bot = nullptr;
	USpriteRenderer* Front_Top = nullptr;
	USpriteRenderer* Front_Bot = nullptr;

	FVector Top = { 25.0f, 80.0f, 0.0f };
	FVector Bot = { 25.0f, 0.0f, 0.0f };
	bool IsStairsUpValue = false;

	FVector Velocity = FVector::Zero;

	UCollision* AttackCol = nullptr;
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

	void WallSlideStart();
	void WallSlide(float _DeltaTime);

	void FlipStart();
	void Flip(float _DeltaTime);

	void ReplayStart();
	void Replay(float _DeltaTime);
		
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
	void DownStairGravityUpdate(float _DeltaTime);
	void RollDownStairGravityUpdate(float _DeltaTime);
	void JumpGravityUpdate(float _DeltaTime);
	void FallGravityUpdate(float _DeltaTime);
	void WallGravityUpdate(float _DeltaTime);

	void JumpVelXUpdate(float _DeltaTime);
	void FallVelXUpdate(float _DeltaTime);
	void IdleToRunVelUpdate(float _DeltaTime);
	void RunToIdleVelUpdate(float _DeltaTime);

	void PosUpdate(float _DeltaTime);

	void ColCheckUpdate();	

// Effect Set (virtual)
protected:
	virtual void SetAttackEffect(const FVector& _Dir) {};

};

