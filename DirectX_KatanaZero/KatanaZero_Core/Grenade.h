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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;

private:
	FVector ShootDir = FVector::Zero;
	float ShootSpeed = 0.0f;

private:
	std::vector<USpriteRenderer*> Explosion;
	const int ExplosionNum = 1;

};

