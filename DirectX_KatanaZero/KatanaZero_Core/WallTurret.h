#pragma once
#include "RecMapCompoBase.h"

// Ό³Έν : HeadHunter WallTurret
class AWallTurret : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constructor destructor
	AWallTurret();
	~AWallTurret();
	
	// delete Function
	AWallTurret(const AWallTurret& _Other) = delete;
	AWallTurret(AWallTurret&& _Other) noexcept = delete;
	AWallTurret& operator=(const AWallTurret& _Other) = delete;
	AWallTurret& operator=(AWallTurret&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;

private:
	void WallOpenAnimAdjust();

private:
	USpriteRenderer* Wall = nullptr;

};

