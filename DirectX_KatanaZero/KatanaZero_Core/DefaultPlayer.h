#pragma once
#include "PlayerBase.h"

// ���� :
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

// Effect Setting
protected:
	void SetAttackEffect(float _Deg) override;

private:
	void CreateAnimation();

private:
	USpriteRenderer* Effect = nullptr;

};

