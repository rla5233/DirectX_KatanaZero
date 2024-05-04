#pragma once
#include <EngineCore/StateManager.h>	

class UKZImage;

// 설명 : Factory 인트로 UI
class AFactoryIntroUI : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AFactoryIntroUI();
	~AFactoryIntroUI();
	
	// delete Function
	AFactoryIntroUI(const AFactoryIntroUI& _Other) = delete;
	AFactoryIntroUI(AFactoryIntroUI&& _Other) noexcept = delete;
	AFactoryIntroUI& operator=(const AFactoryIntroUI& _Other) = delete;
	AFactoryIntroUI& operator=(AFactoryIntroUI&& _Other) noexcept = delete;

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
	void SongBackGroundAnim(float _DeltaTime);
	void PlayingSongTextAnim(float _DeltaTime);
	void PlayingSongTitleAnim(float _DeltaTime);
	void StageNameAnim(float _DeltaTime);
	void StartWaitingAnim(float _DeltaTime);

	float TimeCount = 0.0f;

private:
	UKZImage* SongBackGround = nullptr;
	UKZImage* PlayingSong0 = nullptr;
	UKZImage* PlayingSong1 = nullptr;
	UKZImage* PlayingSongUnderLine = nullptr;
	UKZImage* PlayingSongTitle = nullptr;
	FVector SongUIPos = { 240.0f, -270.0f, 0.0f };

	UKZImage* StageName0 = nullptr;
	UKZImage* StageName1 = nullptr;
	UKZImage* StageNameBackGround = nullptr;
	FVector StageNameUIPos = { 0.0f, 35.0f, 0.0f };
	float NameMoveTimeWeight = 3.0f;

	UImage* StartMsg = nullptr;
	UImage* StartMouse = nullptr;
	float StartMsgPosY = -40.0f;

	EFactoryIntroOrder Order = EFactoryIntroOrder::None;

// FSM
private:
	UStateManager State;
	void StateInit();


};

