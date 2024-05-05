#pragma once
#include <EngineCore/StateManager.h>

class UKZImage;

// Ό³Έν : Factory Clear UI
class UFactoryClearUI : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	UFactoryClearUI();
	~UFactoryClearUI();
	
	// delete Function
	UFactoryClearUI(const UFactoryClearUI& _Other) = delete;
	UFactoryClearUI(UFactoryClearUI&& _Other) noexcept = delete;
	UFactoryClearUI& operator=(const UFactoryClearUI& _Other) = delete;
	UFactoryClearUI& operator=(UFactoryClearUI&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	void On();
	void Off();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ImageInit();

private:
	void FactoryClearStart(float _DeltaTime);
	void FactoryClearEnd(float _DeltaTime);


private:
	UKZImage* ClearText0 = nullptr;
	UKZImage* ClearText1 = nullptr;
	UKZImage* ClearBackGround = nullptr;

	FVector ClearUIPos = { 0.0f, 35.0f, 0.0f };
	float ClearMoveTimeWeight = 1.0f;

	EFactoryClearOrder Order = EFactoryClearOrder::None;

// FSM
private:
	UStateManager State;
	void StateInit();

};

