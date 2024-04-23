#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"
#include "RecordingObject.h"

class CloudEffect
{
public:
	USpriteRenderer* Renderer = nullptr;
	FVector Velocity = FVector::Zero;
};

// 설명 : Player 부모 클래스
class APlayerBase : 
	public AActor, 
	public UPixelColObject,
	public UPhysicsObject,
	public URecordingObject
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

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

	inline std::string GetCurState() const
	{
		return State.GetCurStateName();
	}

	void HitByEnemy();

	// 수정 (삭제 필요)
	void DebugUpdate();
    ///////////////////

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void EffectInit();
	virtual void CollisionInit();

	UCollision* BodyCol = nullptr;
	UCollision* FrontCol = nullptr;

private:
	// 기본 업데이트 함수
	void DefaultUpdate(float _DeltaTime);

	void AttackDelayTimeUpdate(float _DeltaTime);

private:
	// 방향 관련
	bool IsDirChangeKeyDown();
	bool IsDirChangeKeyPress();
	void DirChange(EEngineDir _Dir);

private:
	USpriteRenderer* Body = nullptr;
	USpriteRenderer* AttackEffect = nullptr;
	USpriteRenderer* JumpLandEffect = nullptr;
	std::vector<CloudEffect> Cloud;
	const int CloudSize = 20;
	int CloudIdx = 0;

	USpriteRenderer* Back_Top = nullptr;
	USpriteRenderer* Back_Bot = nullptr;
	USpriteRenderer* Front_Top = nullptr;
	USpriteRenderer* Front_Bot = nullptr;

	UCollision* AttackCol = nullptr;
	FVector AttackDir = FVector::Zero;
	float AttackDelayTimeCount = 0.0f;
	bool CanAttack = true;
	
	bool IsPlayValue = true;
	bool IsColDoorValue = false;
	bool IsInvincibleValue = false;

	UStateManager State;
	void StateInit();

// FSM
protected:
	virtual void IdleStart();
	virtual void Idle(float _DeltaTime);

	virtual void IdleToRunStart();
	virtual void IdleToRun(float _DeltaTime);

	virtual void RunStart();
	virtual void Run(float _DeltaTime);

	virtual void RunToIdleStart();
	virtual void RunToIdle(float _DeltaTime);

	virtual void PostCrouchStart();
	virtual void PostCrouch(float _DeltaTime);

	virtual void PreCrouchStart();
	virtual void PreCrouch(float _DeltaTime);

	virtual void RollStart();
	virtual void Roll(float _DeltaTime);

	virtual void JumpStart();
	virtual void Jump(float _DeltaTime);

	virtual void FallStart();
	virtual void Fall(float _DeltaTime);

	virtual void AttackStart();
	virtual void Attack(float _DeltaTime);

	virtual void WallSlideStart();
	virtual void WallSlide(float _DeltaTime);

	virtual void FlipStart();
	virtual void Flip(float _DeltaTime);

	virtual void ReplayStart();
	virtual void Replay(float _DeltaTime);

	virtual void DeadStart();
	virtual void Dead(float _DeltaTime);
		
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

	bool IsDoorKickInputPress();

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

	// 수정 (간소화)
	void ColCheckUpdate();	

// Collision
private:
	void AttackCollisionCheck();

	void DoorColCheck();


// Effect Set (virtual)
private:
	void EffectVecIdxUpdate();
	void SetAttackEffect(float _Deg);
	void SetJumpEffect();
	void SetLandEffect();
	void SetCroudEffect(int _Num);
	void SetCroudEffectUpdate(float _DeltaTime);
	void CreateRollCroudEffect(float _DeltaTime);
	float CroudTimeCount = 0.0f;
};

