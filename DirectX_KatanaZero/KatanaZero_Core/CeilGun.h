#pragma once
#include "RecMapCompoBase.h"

// º≥∏Ì : √µ¿Â √—
class ACeilGun : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constrcuter destructer
	ACeilGun();
	~ACeilGun();

	// delete Function
	ACeilGun(const ACeilGun& _Other) = delete;
	ACeilGun(ACeilGun&& _Other) noexcept = delete;
	ACeilGun& operator=(const ACeilGun& _Other) = delete;
	ACeilGun& operator=(ACeilGun&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void StateInit() override;
	void RendererInit();
	void CollisionInit();

private:
	USpriteRenderer* Laser = nullptr;
	UCollision* HitCol = nullptr;

};

