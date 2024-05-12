#pragma once
#include "HeadHunterBase.h"

// Ό³Έν : Phase2 HeadHunter
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
	void CreateRifleLaser();
	void CreateDashLaser();
	void CreateDashAttack();
	void CreateSparkEffect();

	void AdjustBodyPosByDir(const FVector _Pos);
	void RifleLaserColCheck();

	void SparkIdxUpdate();

private:
	// Collision
	UCollision* DashAttack = nullptr;
	UCollision* RifleLaserCol;

	// Effect
	USpriteRenderer* RifleLaserEffect;
	std::vector<USpriteRenderer*> AllSparkEffect;

	USpriteRenderer* DashLaser = nullptr;

	// Info.
	float RifleLaserAlpha = 1.0f;

	const int SparkEffectNum = 18;
	int SparkIdx = 0;

	// Pattern Info. //
	// Rifle1
	int Rifle1Count = 3;

	// GunShoot1
	bool IsGunShoot = false;
	bool ReGunShoot = false;
	int GunShootCount = 3;

	// Sword Dash
	float DashLaserAlpha = 0.0f;

	// AirRifle1
	float AirRifle1FirstDeg = 0.0f;
	float AirRifle1DegInter = 0.0f;
	float AirRifle1DegCount = 0.0f;
	int AirRifle1ShootCount = 0;
	bool IsAirRifleShake = false;

	// AirRifle2
	float AirRifle2TimeCount = 0.0f;

	// Complex 
	float AirPosY = 520.0f;
	std::vector<float> AirPosX = { 235.0f, 1120.0f, 350.0f, 1000.0f };
	int AirLaserCount = 0;
	float SweepLaserDeg1 = 235.0f;
	float SweepLaserDeg2 = 305.0f;
	float ComplexSweepLaserTimeCount = 0.0f;

	float PatternDelayTimeCount = 0.0f;

// FSM
private:
	void IdleStart() override;
	void Idle(float _DeltaTime) override;

	void HitFlyStart() override;

	void PatternRifle1Start();
	void PatternRifle1(float _DeltaTime);

	void PatternGunShoot1Start();
	void PatternGunShoot1(float _DeltaTime);

	void PatternSwordDashStart();
	void PatternSwordDash(float _DeltaTime);

	void PatternAirRifle1Start();
	void PatternAirRifle1(float _DeltaTime);

	void PatternAirRifle2Start();
	void PatternAirRifle2(float _DeltaTime);

	void PatternComplexStart();
	void PatternComplex(float _DeltaTime);

	void PatternBombingStart();
	void PatternBombing(float _DeltaTime);

// Effect
private:
	void SetRifle1LaserEffect();
	void SetAirRifle1Effect();

	void SetAirRifle2Effect();
	void SetAirRifle2Effect1();
	
	void SetComplexLaser1Effect();
	void SetComplexLaser2Effect();

// Pattern
private:
	void PatternCheck();

	// Pattern_Rifle1
	void Rifle1LaserUpdate(float _DeltaTime);
	void Rifle1LaserUpdate1(float _DeltaTime);
	void Rifle1LaserUpdate2(float _DeltaTime);
	void Rifle1LaserUpdate3(float _DeltaTime);

	// Pattern_GunShoot1
	void GunShoot1Update(float _DeltaTime);
	void GunShoot1Update1(float _DeltaTime);
	
	// Pattern_SwordDash
	void SwordDashUpdate(float _DeltaTime);
	void SwordDashUpdate1(float _DeltaTime);

	// Pattern_AirRifle1
	void AirRifle1Update(float _DeltaTime);
	void AirRifle1Update1(float _DeltaTime);
	void AirRifle1Update2(float _DeltaTime);
	void AirRifle1Update3(float _DeltaTime);

	// Pattern_AirRifle2
	void AirRifle2Update(float _DeltaTime);
	void AirRifle2Update1(float _DeltaTime);
	void AirRifle2Update2(float _DeltaTime);
	void AirRifle2Update3(float _DeltaTime);

	// Pattern_Complex
	void ComplexUpdate(float _DeltaTime);
	void ComplexUpdate1(float _DeltaTime);
	void ComplexUpdate2(float _DeltaTime);
	void ComplexUpdate3(float _DeltaTime);
	void ComplexUpdate4(float _DeltaTime);
	void ComplexUpdate5(float _DeltaTime);
	void ComplexUpdate6(float _DeltaTime);
	void ComplexUpdate7(float _DeltaTime);
	void ComplexUpdate8(float _DeltaTime);
	void ComplexUpdate9(float _DeltaTime);
	void ComplexUpdate10(float _DeltaTime);
	void ComplexUpdate11(float _DeltaTime);

	// Pattern_Bombing
	void BombingUpdate(float _DeltaTime);
	void BombingUpdate1(float _DeltaTime);


};

