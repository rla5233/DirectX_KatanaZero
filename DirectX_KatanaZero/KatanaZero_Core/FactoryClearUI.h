#pragma once
#include <EngineCore/StateManager.h>

class UKZImage;

// Ό³Έν : Factory Clear UI
class FactoryClearUI : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	FactoryClearUI();
	~FactoryClearUI();
	
	// delete Function
	FactoryClearUI(const FactoryClearUI& _Other) = delete;
	FactoryClearUI(FactoryClearUI&& _Other) noexcept = delete;
	FactoryClearUI& operator=(const FactoryClearUI& _Other) = delete;
	FactoryClearUI& operator=(FactoryClearUI&& _Other) noexcept = delete;



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ImageInit();

private:
	UKZImage* ClearText0 = nullptr;
	UKZImage* ClearText1 = nullptr;
	UKZImage* ClearTextBackGround = nullptr;

};

