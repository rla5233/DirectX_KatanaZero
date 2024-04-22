#pragma once
#include <EngineCore/StateManager.h>

// 설명 : 리플레이 UI
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

// 초기 Setting 함수
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

