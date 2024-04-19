#pragma once
#include "RecMapCompoBase.h"

// 설명 : 문 오브젝트
class ADoor : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase)
public:
	// constrcuter destructer
	ADoor();
	~ADoor();

	// delete Function
	ADoor(const ADoor& _Other) = delete;
	ADoor(ADoor&& _Other) noexcept = delete;
	ADoor& operator=(const ADoor& _Other) = delete;
	ADoor& operator=(ADoor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit() override;
	void RendererInit();
	void CollisionInit();

private:
	UCollision* BodyCol = nullptr;
	UCollision* HitCol = nullptr;

//FSM
private:


};

