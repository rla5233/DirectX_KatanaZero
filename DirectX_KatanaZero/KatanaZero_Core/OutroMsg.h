#pragma once
#include <EngineCore/StateManager.h>

// ���� : Outro �޽���
class AOutroMsg : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AOutroMsg();
	~AOutroMsg();

	// delete Function
	AOutroMsg(const AOutroMsg& _Other) = delete;
	AOutroMsg(AOutroMsg&& _Other) noexcept = delete;
	AOutroMsg& operator=(const AOutroMsg& _Other) = delete;
	AOutroMsg& operator=(AOutroMsg&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* Body = nullptr;


private:
	UStateManager State;

	void StateInit();
	
};

