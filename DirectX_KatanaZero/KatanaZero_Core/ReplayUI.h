#pragma once
#include <EngineCore/StateManager.h>

class APlayLevelBase;

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

	void On();
	void Off();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

// 초기 Setting 함수
private:
	void ImageInit();

private:
	USpriteRenderer* Mouse = nullptr;
	UImage* LeftTopText = nullptr;
	UImage* Speed = nullptr;
	UImage* RightBottomText = nullptr;

	APlayLevelBase* PlayLevel = nullptr;
	int SpeedIdx = 0;

// FSM
private:
	UStateManager State;
	
	void StateInit();

	void MousePosUpdate();
	void SetFastSpeedImage();
	void SetRewindSpeedImage();
};

