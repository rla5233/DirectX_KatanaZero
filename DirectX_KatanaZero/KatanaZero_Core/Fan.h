#pragma once
#include "RecMapCompoBase.h"

// Ό³Έν : Factory_004 AFan
class AFan : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase);
public:
	// constrcuter destructer
	AFan();
	~AFan();

	// delete Function
	AFan(const AFan& _Other) = delete;
	AFan(AFan&& _Other) noexcept = delete;
	AFan& operator=(const AFan& _Other) = delete;
	AFan& operator=(AFan&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RendererInit();
	void CollisionInit();
	void StateInit() override;

private:
	USpriteRenderer* Back = nullptr;
	USpriteRenderer* Front = nullptr;
	USpriteRenderer* Blade = nullptr;

	UCollision* BodyCol = nullptr;

};

