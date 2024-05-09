#pragma once
#include <EngineCore/StateManager.h>

#include "RecordingObject.h"
#include "PhysicsObject.h"
#include "PixelColObject.h"
#include "HeadHunterEffect.h"
#include "AfterImageObject.h"

// ���� : HeadHunter
class AHeadHunterBase : 
	public AActor,
	public URecordingObject,
	public UPhysicsObject,
	public UPixelColObject,
	public UAfterImageObject
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AHeadHunterBase();
	~AHeadHunterBase();
	
	// delete Function
	AHeadHunterBase(const AHeadHunterBase& _Other) = delete;
	AHeadHunterBase(AHeadHunterBase&& _Other) noexcept = delete;
	AHeadHunterBase& operator=(const AHeadHunterBase& _Other) = delete;
	AHeadHunterBase& operator=(AHeadHunterBase&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline void SubStateChange(std::string_view _State)
	{
		SubState.ChangeState(_State);
	}

	inline void SetDir(EEngineDir _Dir)
	{
		Body->SetDir(_Dir);
	}

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

	inline bool IsDead() const
	{
		return IsDeadValue;
	}

	void HitByPlayer(FVector _AttDir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void CollisionInit();
	virtual void CreateAnimation();

private:
	void CreateRecoverEffect();
	void CreateCloudEffect();
	void RendererInit();
	
protected:
	void ColCheckUpdate();
	void SetVelocityByDir(const FVector& _Vel);
	void AddVelocityByDir(const FVector& _Vel);

protected:
	// Renderer
	USpriteRenderer* Body = nullptr;	
	std::vector<URecoverEffect> AllRecoverEffect;

	std::vector<UCloudEffect> Cloud;
	float CroudTimeCount = 0.0f;
	const int CloudSize = 15;
	int CloudIdx = 0;

	// Collision
	UCollision* BodyCol = nullptr;

	// Info.
	FVector HitDir = FVector::Zero;
	bool IsDeadValue = false;
	int PatternOrder = 0;
	int RollCount = 0;
	int Hp = 0;

// FSM
protected:
	UStateManager State;
	virtual void StateInit();

	virtual void IdleStart();
	virtual void Idle(float _DeltaTime);

	void RollStart();
	void Roll(float _DeltaTime);

	virtual void HitFlyStart();
	void HitFly(float _DeltaTime);

	virtual void RecoverStart();
	void Recover(float _DletaTime);

// Sub FSM
protected:
	UStateManager SubState;
	void SubStateInit();

	void WaitStart();
	void Wait(float _DeltaTime);

	virtual void PlayStart();
	void Play(float _DeltaTime);

	virtual void RestartStart();
	void Restart(float _DeltaTime);

// Effect
private:
	void SetRollCroudEffect(float _DeltaTime);
	void CroudEffectUpdate(float _DeltaTime);
	
	void SetRecoverEffect();

};

