#pragma once
#include "PlayerBase.h"

// Ό³Έν :
class ADefaultPlayer : public APlayerBase
{
	GENERATED_BODY(APlayerBase)
public:
	// constrcuter destructer
	ADefaultPlayer();
	~ADefaultPlayer();

	// delete Function
	ADefaultPlayer(const ADefaultPlayer& _Other) = delete;
	ADefaultPlayer(ADefaultPlayer&& _Other) noexcept = delete;
	ADefaultPlayer& operator=(const ADefaultPlayer& _Other) = delete;
	ADefaultPlayer& operator=(ADefaultPlayer&& _Other) noexcept = delete;

	inline void SetIntroRunTime(float _Time)
	{
		IntroRunTime = _Time;
	}

	inline void SetIntroType(EIntroType _Value)
	{
		IntroType = _Value;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionInit() override;

private:
	void CreateAnimation();
	void SoundSetting();
	
private:
	float IntroRunTime = 0.5f;

	EIntroType IntroType = EIntroType::Default;

// FSM
protected:
	// Main State
	void IdleStart() override;
	void IdleToRunStart() override;
	void RunStart() override;
	void RunToIdleStart() override;
	void PostCrouchStart() override;
	void PreCrouchStart() override;
	void RollStart() override;
	void JumpStart() override;
	void FallStart() override;
	void AttackStart() override;
	void WallSlideStart() override;
	void FlipStart() override;
	void KickDoorStart() override;
	void DeadStart() override;	
	void OnlyFallStart() override;

protected:
	// Sub State
	void IntroStart() override;
	void Intro(float _DeltaTime) override;

protected:
	void OutroTypeInit() override;
	void OutroUpdate(float _DeltaTime) override;

};

