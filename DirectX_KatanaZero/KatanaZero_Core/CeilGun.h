#pragma once
#include "RecMapCompoBase.h"
#include "PhysicsObject.h"

// º≥∏Ì : √µ¿Â √—
class ACeilGun : public ARecMapCompoBase, public UPhysicsObject
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

	void SetPointX(float _Left, float _Right)
	{
		LeftPoint_X = _Left;
		RightPoint_X = _Right;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void StateInit() override;
	void RendererInit();
	void CollisionInit();

private:
	USpriteRenderer* Laser = nullptr;
	USpriteRenderer* Spark = nullptr;
	USpriteRenderer* Smoke = nullptr;
	UCollision* HitCol = nullptr;

	float LeftPoint_X = 0.0f;
	float RightPoint_X = 0.0f;

private:
	void SetRandomSparkAnim();
	void SetRandomSmokeAnim();

};

