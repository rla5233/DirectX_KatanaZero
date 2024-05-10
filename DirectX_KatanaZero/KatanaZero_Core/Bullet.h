#pragma once
#include "RecMapCompoBase.h"
#include "PhysicsObject.h"
#include "PixelColObject.h"

// Ό³Έν : HeadHunter2 Bullet
class ABullet : 
	public ARecMapCompoBase, 
	public UPhysicsObject,
	public UPixelColObject
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constructor destructor
	ABullet();
	~ABullet();
	
	// delete Function
	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline void SetShootDir(const FVector& _Dir)
	{
		ShootDir = _Dir.Normalize2DReturn();
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;

private:
	FVector ShootDir = FVector::Zero;

private:
	UCollision* BodyCol = nullptr;

};

