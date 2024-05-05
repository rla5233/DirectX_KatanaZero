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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void RendererInit();
	void CollisionInit();
	void CreateAnimation();




// FSM
private:
	UStateManager State;
	void StateInit();

};

