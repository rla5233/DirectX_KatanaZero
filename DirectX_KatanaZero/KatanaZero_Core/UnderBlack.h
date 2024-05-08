#pragma once
#include "RecMapCompoBase.h"

// ���� : HeadHunter1 ���� �ٴ�
class AUnderBlack : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase);
public:
	// constrcuter destructer
	AUnderBlack();
	~AUnderBlack();

	// delete Function
	AUnderBlack(const AUnderBlack& _Other) = delete;
	AUnderBlack(AUnderBlack&& _Other) noexcept = delete;
	AUnderBlack& operator=(const AUnderBlack& _Other) = delete;
	AUnderBlack& operator=(AUnderBlack&& _Other) noexcept = delete;
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float Alpha = 0.0f;

private:
	void StateInit() override;

};

