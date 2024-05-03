#pragma once
#include <EngineCore/StateManager.h>

// 설명 : Msg 클래스
class AFailedMsg : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AFailedMsg();
	~AFailedMsg();

	// delete Function
	AFailedMsg(const AFailedMsg& _Other) = delete;
	AFailedMsg(AFailedMsg&& _Other) noexcept = delete;
	AFailedMsg& operator=(const AFailedMsg& _Other) = delete;
	AFailedMsg& operator=(AFailedMsg&& _Other) noexcept = delete;

	void StateChange(std::string_view _State)
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
	UImage* Body = nullptr;
	UImage* BackGround = nullptr;

private:
	UStateManager State;
	void StateInit();

};

