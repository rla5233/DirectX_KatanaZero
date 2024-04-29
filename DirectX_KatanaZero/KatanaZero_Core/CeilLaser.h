#pragma once
#include "RecMapCompoBase.h"

// ���� : õ�� ������
class ACeilLaser : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constrcuter destructer
	ACeilLaser();
	~ACeilLaser();

	// delete Function
	ACeilLaser(const ACeilLaser& _Other) = delete;
	ACeilLaser(ACeilLaser&& _Other) noexcept = delete;
	ACeilLaser& operator=(const ACeilLaser& _Other) = delete;
	ACeilLaser& operator=(ACeilLaser&& _Other) noexcept = delete;

	void AddLaserScaleY(float _ScaleY);
	void AddLaserPositionY(float _PosY);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;
	void RendererInit();
	void CollisionInit();

private:
	USpriteRenderer* Laser = nullptr;
	UCollision* HitCol = nullptr;

	float AddScaleOnLaserY = 0.0f;

};

