#pragma once
#include <EngineCore/StateManager.h>

#include "RecordingObject.h"
#include "PhysicsObject.h"
#include "PixelColObject.h"
#include "HeadHunterEffect.h"
#include "AfterImageObject.h"

// Ό³Έν : HeadHunter
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

	void HitByPlayer(FVector _AttDir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateRecoverEffect();

	void RendererInit();
	void CollisionInit();
	void CreateAnimation();
	
private:
	void LaserColCheck();
	void ColCheckUpdate();

protected:
	void SetVelocityByDir(const FVector& _Vel);
	void AddVelocityByDir(const FVector& _Vel);

protected:
	// Renderer
	USpriteRenderer* Body = nullptr;
	USpriteRenderer* LaserEffect = nullptr;
	float LaserAlpha = 1.0f;
	
	std::vector<URecoverEffect> AllRecoverEffect;


	// Collision
	UCollision* BodyCol = nullptr;
	UCollision* LaserCol = nullptr;


	// Info.
	FVector HitDir = FVector::Zero;
	int PatternOrder = 0;

// FSM
protected:
	UStateManager State;
	virtual void StateInit();

	void IdleStart();
	virtual void Idle(float _DeltaTime);

	void HitFlyStart();
	void HitFly(float _DeltaTime);

	virtual void RecoverStart();
	void Recover(float _DletaTime);

	void PatternRifle1Start();
	void PatternRifle1(float _DeltaTime);


// Sub FSM
protected:
	UStateManager SubState;
	void SubStateInit();

	void WaitStart();
	void Wait(float _DeltaTime);

	void PlayStart();
	virtual void Play(float _DeltaTime);

	void RestartStart();
	void Restart(float _DeltaTime);

// Effect
private:
	void SetRifle1LaserEffect();
	void Rifle1LaserEffectUpdate1(float _DeltaTime);
	void Rifle1LaserEffectUpdate2(float _DeltaTime);
	void Rifle1LaserEffectUpdate3(float _DeltaTime);

	void SetRecoverEffect();

};

