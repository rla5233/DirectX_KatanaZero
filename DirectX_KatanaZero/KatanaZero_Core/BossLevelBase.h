#pragma once
#include <EngineCore/StateManager.h>

class ADefaultPlayer;
class AColMapObject;
class AMainCamera;
class AFailedMsg;
class AMouseAim;
class AUp_HUD;

class ADiamondTransition;
class UWaveEffect;

// 설명 : BossLevel 기본 클래스
class ABossLevelBase : public AGameMode
{
	GENERATED_BODY(AGameMode)	
public:
	// constructor destructor
	ABossLevelBase();
	~ABossLevelBase();
	
	// delete Function
	ABossLevelBase(const ABossLevelBase& _Other) = delete;
	ABossLevelBase(ABossLevelBase&& _Other) noexcept = delete;
	ABossLevelBase& operator=(const ABossLevelBase& _Other) = delete;
	ABossLevelBase& operator=(ABossLevelBase&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

protected:
	// Object
	std::shared_ptr<AMainCamera> MainCamera = nullptr;
	std::shared_ptr<AMouseAim> Aim = nullptr;
	std::shared_ptr<AColMapObject> ColMap = nullptr;

	std::shared_ptr<ADefaultPlayer> Player = nullptr;

	// UI
	std::shared_ptr<AUp_HUD> HUD = nullptr;

	// Msg
	std::shared_ptr<AFailedMsg> FailedMsg = nullptr;
	
	// Effect
	std::shared_ptr<UWaveEffect> WaveEffect = nullptr;
	std::shared_ptr<ADiamondTransition> DiaTransition = nullptr;


	// Stage Info.
	float TotalPlayTime = 0.0f;
	float PlayTimeCount = 0.0f;


private:
	UStateManager State;
	void StateInit();

};

