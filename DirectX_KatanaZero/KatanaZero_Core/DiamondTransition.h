#pragma once
#include <EngineCore/StateManager.h>

// 설명 : 스테이지 전환 Transition
class ADiamondTransition : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ADiamondTransition();
	~ADiamondTransition();

	// delete Function
	ADiamondTransition(const ADiamondTransition& _Other) = delete;
	ADiamondTransition(ADiamondTransition&& _Other) noexcept = delete;
	ADiamondTransition& operator=(const ADiamondTransition& _Other) = delete;
	ADiamondTransition& operator=(ADiamondTransition&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateInit();

private:
	std::vector<std::vector<USpriteRenderer*>> AllRenderer;
	const int Width = 40;
	const int Height = 23;
	
	float TimeCount = 0.0f;
	int X = 0;
	int Y = 0;

private:
	UStateManager State;

};

