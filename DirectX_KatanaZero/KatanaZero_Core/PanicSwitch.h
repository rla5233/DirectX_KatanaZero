#pragma once
#include "RecMapCompoBase.h"

// ���� : ����ġ Ŭ����
class APanicSwitch : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase);
public:
	// constrcuter destructer
	APanicSwitch();
	~APanicSwitch();

	// delete Function
	APanicSwitch(const APanicSwitch& _Other) = delete;
	APanicSwitch(APanicSwitch&& _Other) noexcept = delete;
	APanicSwitch& operator=(const APanicSwitch& _Other) = delete;
	APanicSwitch& operator=(APanicSwitch&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void StateInit() override;
	void RendererInit();
	void CollisionInit();

private:
	UCollision* BodyCol = nullptr;

};

