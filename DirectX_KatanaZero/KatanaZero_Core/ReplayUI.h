#pragma once
#include <EngineCore/StateManager.h>

// ���� : ���÷��� UI
class AReplayUI : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AReplayUI();
	~AReplayUI();

	// delete Function
	AReplayUI(const AReplayUI& _Other) = delete;
	AReplayUI(AReplayUI&& _Other) noexcept = delete;
	AReplayUI& operator=(const AReplayUI& _Other) = delete;
	AReplayUI& operator=(AReplayUI&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

// �ʱ� Setting �Լ�
private:
	void ImageInit();

private:
	USpriteRenderer* Mouse = nullptr;
	UImage* LeftTopText = nullptr;
	UImage* RightBottomText = nullptr;

// FSM
private:
	UStateManager State;

	void StateInit();

	void MousePosUpdate();
};

