#pragma once
#include "PlayerBase.h"

// Ό³Έν :
class ADefaultPlayer : public APlayerBase
{
	GENERATED_BODY(APlayerBase)
public:
	// constrcuter destructer
	ADefaultPlayer();
	~ADefaultPlayer();

	// delete Function
	ADefaultPlayer(const ADefaultPlayer& _Other) = delete;
	ADefaultPlayer(ADefaultPlayer&& _Other) noexcept = delete;
	ADefaultPlayer& operator=(const ADefaultPlayer& _Other) = delete;
	ADefaultPlayer& operator=(ADefaultPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionInit() override;

private:
	void CreateAnimation();

};

