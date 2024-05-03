#pragma once
#include <EngineCore/StateManager.h>

class UFadeImage;

// 설명 : Outro 메시지
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

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	void On();
	void Off();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UFadeImage* Body = nullptr;
	
	UStateManager State;
	void StateInit();
};

