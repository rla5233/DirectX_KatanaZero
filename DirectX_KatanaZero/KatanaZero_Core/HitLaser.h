#pragma once
#include "PhysicsObject.h"

// 설명 : 피격시 Laesr Effect
class AHitLaser : public AActor, public UPhysicsObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AHitLaser();
	~AHitLaser();

	// delete Function
	AHitLaser(const AHitLaser& _Other) = delete;
	AHitLaser(AHitLaser&& _Other) noexcept = delete;
	AHitLaser& operator=(const AHitLaser& _Other) = delete;
	AHitLaser& operator=(AHitLaser&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;

};

