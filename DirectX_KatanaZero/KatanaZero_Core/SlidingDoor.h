#pragma once
#include "RecMapCompoBase.h"

// Ό³Έν : SlidingDoor
class ASlidingDoor : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase);
public:
	// constructor destructor
	ASlidingDoor();
	~ASlidingDoor();
	
	// delete Function
	ASlidingDoor(const ASlidingDoor& _Other) = delete;
	ASlidingDoor(ASlidingDoor&& _Other) noexcept = delete;
	ASlidingDoor& operator=(const ASlidingDoor& _Other) = delete;
	ASlidingDoor& operator=(ASlidingDoor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetAllMulColor(const float4& _MulColor) override;

private:
	void RendererInit();
	void CreateAnimation();

	void StateInit() override;
	
private:
	USpriteRenderer* DoorLED = nullptr;

};

