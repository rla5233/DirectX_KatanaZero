#pragma once
#include <EngineCore/StateManager.h>

#include "RecordingObject.h"
#include "PhysicsObject.h"
#include "PixelColObject.h"

// Ό³Έν : HeadHunter
class AHeadHunter : 
	public AActor,
	public URecordingObject,
	public UPhysicsObject,
	public UPixelColObject
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AHeadHunter();
	~AHeadHunter();
	
	// delete Function
	AHeadHunter(const AHeadHunter& _Other) = delete;
	AHeadHunter(AHeadHunter&& _Other) noexcept = delete;
	AHeadHunter& operator=(const AHeadHunter& _Other) = delete;
	AHeadHunter& operator=(AHeadHunter&& _Other) noexcept = delete;

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void RendererInit();
	void CollisionInit();
	void CreateAnimation();

private:
	USpriteRenderer* Body = nullptr;
	

// FSM
private:
	UStateManager State;
	void StateInit();

	void IdleStart();
	void Idle(float _DeltaTime);

	void PatternRifle1Start();
	void PatternRifle1(float _DeltaTime);


// Sub FSM
private:
	UStateManager SubState;
	void SubStateInit();

	void WaitStart();
	void Wait(float _DeltaTime);

	void PlayStart();
	void Play(float _DeltaTime);

};

