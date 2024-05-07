#pragma once
#include <EngineCore/StateManager.h>
#include "PixelColObject.h"
#include "PhysicsObject.h"
#include "RecordingObject.h"
#include "AfterImageObject.h"

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
	public URecordingObject,
	public UAfterImageObject
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

	inline void SubStateChange(std::string_view _State)
	{
		SubState.ChangeState(_State);
	}

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

	inline std::string GetCurMainState() const
	{
		return State.GetCurStateName();
	}

	inline void SetIsPlayValue(bool _PlayValue)
	{
		IsPlayValue = _PlayValue;
	}

	inline bool IsAbilityOn() const
	{
		return IsAbilityValue;
	}

	inline bool IsDead() const
	{
		return PlayerState::dead == State.GetCurStateName();
	}

	inline EIntroOrder GetIntroOrder() const
	{
		return IntroOrder;
	}

	inline void SetIntroOrder(EIntroOrder _IntroOrder)
	{
		IntroOrder = _IntroOrder;
	}
	 
	inline EOutroType GetOutroType() const
	{
		return OutroType;
	}

	inline void SetOutroType(EOutroType _OutroType)
	{
		OutroType = _OutroType;
	}

	inline int GetFloorNum() const
	{
		return FloorNum;
	}

	inline EEnemyType GetHitEnemyType() const
	{
		return HitEnemy;
	}

	void DirChange(EEngineDir _Dir);

	void HitByEnemy(FVector _HitDir, EEnemyType _EnemyType = EEnemyType::Default);

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
	// 방향 관련
	bool IsDirChangeKeyDown();
	bool IsDirChangeKeyPress();

private:
	// Renderer
	USpriteRenderer* Body = nullptr;
	USpriteRenderer* AttackEffect = nullptr;
	USpriteRenderer* JumpLandEffect = nullptr;
	std::vector<CloudEffect> Cloud;
	static const int CloudSize;
	int CloudIdx = 0;

	USpriteRenderer* Back_Top = nullptr;
	USpriteRenderer* Back_Bot = nullptr;
	USpriteRenderer* Front_Top = nullptr;
	USpriteRenderer* Front_Bot = nullptr;

	// Attack
	UCollision* AttackCol = nullptr;
	FVector AttackDir = FVector::Zero;
	float AttackDelayTimeCount = 0.0f;
	bool CanAttack = true;

	// Ability
	float AbilityTime = Const::player_ability_time;
	bool IsAbilityValue = false;
	
	// etc.
	int FloorNum = 0;
	bool IsPlayValue = false;
	bool IsColDoorValue = false;
	bool IsInvincibleValue = false;
	EEnemyType HitEnemy = EEnemyType::Default;
	FVector HitDir = FVector::Zero;

	// FSM
	UStateManager State;	
	void StateInit();	

	UStateManager SubState;
	void SubStateInit();

	EIntroOrder IntroOrder = EIntroOrder::Run;
	EOutroType OutroType = EOutroType::Run;

private:
	void AttackDelayTimeUpdate(float _DeltaTime);
	void AbilityUpdate(float _DeltaTime);
	void AbilityCheck();

// FSM
protected:
	// Main State
	virtual void IdleStart();
	void Idle(float _DeltaTime);

	virtual void IdleToRunStart();
	void IdleToRun(float _DeltaTime);

	virtual void RunStart();
	void Run(float _DeltaTime);

	virtual void RunToIdleStart();
	void RunToIdle(float _DeltaTime);

	virtual void PostCrouchStart();
	void PostCrouch(float _DeltaTime);

	virtual void PreCrouchStart();
	void PreCrouch(float _DeltaTime);

	virtual void RollStart();
	void Roll(float _DeltaTime);

	virtual void JumpStart();
	void Jump(float _DeltaTime);

	virtual void FallStart();
	void Fall(float _DeltaTime);

	virtual void AttackStart();
	void Attack(float _DeltaTime);

	virtual void WallSlideStart();
	void WallSlide(float _DeltaTime);

	virtual void FlipStart();
	void Flip(float _DeltaTime);
	
	virtual void KickDoorStart();
	void KickDoor(float _DeltaTime);

	virtual void DeadStart();
	void Dead(float _DeltaTime);
		
protected:
	// Sub State
	virtual void IntroStart();
	virtual void Intro(float _DeltaTime);
	void IntroEnd();

	void PlayStart();
	void Play(float _DeltaTime);

	void ReplayStart();
	void RePlay(float _DeltaTime);

	void OutroStart();
	void Outro(float _DeltaTime);

	void ReStartStart();
	void ReStart(float _DeltaTime);


	virtual void OutroTypeInit();
	virtual void OutroUpdate(float _DeltaTime);

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

	bool IsAbilityInputDown();
	bool IsAbilityInputPress();
	bool IsAbilityInputUp();

// FSM Setting
protected:
	void SetMaxRunVel();
	void SetAttackDir();

// FSM Update
protected:
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

// Effect
private:
	void EffectVecIdxUpdate();
	void SetAttackEffect(float _Deg);
	void SetJumpEffect();
	void SetLandEffect();
	void SetWallJumpEffet();
	void SetCroudEffect(int _Num);
	void SetWallSlideCroudEffect(int _Num);
	void SetCroudEffectUpdate(float _DeltaTime);
	void CreateRollCroudEffect(float _DeltaTime);
	void CreateWallSlideCroudEffect(float _DeltaTime);
	float CroudTimeCount = 0.0f;

};

