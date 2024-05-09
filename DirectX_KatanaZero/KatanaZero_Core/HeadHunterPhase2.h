#pragma once
#include "HeadHunterBase.h"

// ���� : Phase2 HeadHunter
class AHeadHunterPhase2 : public AHeadHunterBase
{
	GENERATED_BODY(AHeadHunterBase)
public:
	// constructor destructor
	AHeadHunterPhase2();
	~AHeadHunterPhase2();
	
	// delete Function
	AHeadHunterPhase2(const AHeadHunterPhase2& _Other) = delete;
	AHeadHunterPhase2(AHeadHunterPhase2&& _Other) noexcept = delete;
	AHeadHunterPhase2& operator=(const AHeadHunterPhase2& _Other) = delete;
	AHeadHunterPhase2& operator=(AHeadHunterPhase2&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void CreateAnimation() override;
	void StateInit() override;

private:
	void CreateDashLaser();
	void CreateDashAttack();

	void AdjustBodyPosByDir(const FVector _Pos);

private:
	// Collision
	UCollision* DashAttack = nullptr;

	// Effect
	USpriteRenderer* DashLaser = nullptr;

	// Info.
	bool IsGunShoot = false;
	bool ReGunShoot = false;
	int GunShootCount = 3;

	float DashLaserAlpha = 0.0f;

	float PatternDelayTimeCount = 0.0f;
	

// FSM
private:
	void IdleStart() override;
	void Idle(float _DeltaTime) override;

	void PatternGunShoot1Start();
	void PatternGunShoot1(float _DeltaTime);

	void PatternSwordDashStart();
	void PatternSwordDash(float _DeltaTime);

// Effect
private:
	void SetGunShoot1Effect();
	void GunShoot1EffectUpdate();
	
// Pattern
private:
	void PatternCheck();

	// Pattern_GunShoot1
	void GunShoot1Update(float _DeltaTime);
	void GunShoot1Update1(float _DeltaTime);
	
	// Pattern_SwordDash
	void SwordDashUpdate(float _DeltaTime);
	void SwordDashUpdate1(float _DeltaTime);


};

