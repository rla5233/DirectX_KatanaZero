#pragma once
#include <EngineCore/StateManager.h>	

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
	void SongTextAnim(float _DeltaTime);

	float TimeCount = 0.0f;

private:
	UImage* SongBackGround = nullptr;
	UImage* PlayingSong0 = nullptr;
	UImage* PlayingSong1 = nullptr;
	FVector SongUIPos = { 240.0f, -270.0f, 0.0f };


	EFactoryIntroOrder Order = EFactoryIntroOrder::None;

// FSM
private:
	UStateManager State;
	void StateInit();


};

