#pragma once
#include "RecMapCompoBase.h"
#include "PhysicsObject.h"
#include "PixelColObject.h"

// Ό³Έν : GunShoot Grenade
class AGrenade : 
	public ARecMapCompoBase,
	public UPhysicsObject,
	public UPixelColObject
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constrcuter destructer
	AGrenade();
	~AGrenade();

	// delete Function
	AGrenade(const AGrenade& _Other) = delete;
	AGrenade(AGrenade&& _Other) noexcept = delete;
	AGrenade& operator=(const AGrenade& _Other) = delete;
	AGrenade& operator=(AGrenade&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline void SetShootDir(const FVector& _Dir)
	{
		ShootDir = _Dir;
	}

	inline void SetShootSpeed(float _Speed)
	{
		ShootSpeed = _Speed;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;

private:
	FVector ShootDir = FVector::Zero;
	float ShootTimeCount = 0.0f;
	float ShootSpeed = 0.0f;

private:
	UCollision* BodyCol = nullptr;
	USpriteRenderer* Circle = nullptr;
	std::vector<USpriteRenderer*> Explosion;
	const int ExplosionNum = 30;

	float CircleScale = 0.0f;
	float CircleAlpha = 1.0f;

	int ExplosionOrder = 0;

private:
	void ExplosionUpdate(float _DeltaTime);
	void ExplosionUpdate1(float _DeltaTime);
	void ExplosionUpdate2(float _DeltaTime);

};

