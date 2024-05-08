#pragma once
#include "PhysicsObject.h"

// 설명 : SlidingDoor Cloud 효과
class ACloud : public AActor, public UPhysicsObject
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ACloud();
	~ACloud();
	
	// delete Function
	ACloud(const ACloud& _Other) = delete;
	ACloud(ACloud&& _Other) noexcept = delete;
	ACloud& operator=(const ACloud& _Other) = delete;
	ACloud& operator=(ACloud&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;

};

