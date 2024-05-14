#pragma once
#include "RecMapCompoBase.h"
#include "PixelColObject.h"
#include "PhysicsObject.h"

// Ό³Έν : 
class AScientistHead : 
	public ARecMapCompoBase,
	public UPhysicsObject,
	public UPixelColObject
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constructor destructor
	AScientistHead();
	~AScientistHead();
	
	// delete Function
	AScientistHead(const AScientistHead& _Other) = delete;
	AScientistHead(AScientistHead&& _Other) noexcept = delete;
	AScientistHead& operator=(const AScientistHead& _Other) = delete;
	AScientistHead& operator=(AScientistHead&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;

private:

};

