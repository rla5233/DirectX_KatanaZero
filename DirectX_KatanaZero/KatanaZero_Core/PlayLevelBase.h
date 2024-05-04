#pragma once
#include <EngineCore/StateManager.h>

#include "SpawnManager.h"

class AMainCamera;
class AColMapObject;
class ARecMapCompoBase;
class ADiamondTransition;
class ADefaultPlayer;
class AEnemyBase;
class AMouseAim;
class AReplayUI;
class AUp_HUD;
class AStair;
class ADoor;
class AGo;

class AOutroMsg;
class AFailedMsg;

class UGrayScaleEffect;
class UWaveEffect;


// 설명 : PlayLevel 기본 클래스
class APlayLevelBase : public AGameMode, public USpawnManager
{
	friend USpawnManager;

	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	APlayLevelBase();
	~APlayLevelBase();
	
	// delete Function
	APlayLevelBase(const APlayLevelBase& _Other) = delete;
	APlayLevelBase(APlayLevelBase&& _Other) noexcept = delete;
	APlayLevelBase& operator=(const APlayLevelBase& _Other) = delete;
	APlayLevelBase& operator=(APlayLevelBase&& _Other) noexcept = delete;

	void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline std::shared_ptr<AColMapObject> GetColMap() const
	{
		return ColMap;
	}

	inline AMainCamera* GetKZMainCamera() const
	{
		return MainCamera.get();
	}

	inline ADefaultPlayer* GetDefaultPlayer() const
	{
		return Player.get();
	}

	inline float GetTotalPlayTime() const
	{
		return TotalPlayTime;
	}

	inline void EnemyDeadUpdate()
	{
		--TotalEnemy;

#ifdef _DEBUG
		if (0 > TotalEnemy)
		{
			MsgBoxAssert("적의 수 음수가 되었습니다.");
			return;
		}
#endif // _DEBUG
	}

	bool IsCloseDoor(float _StartX, float _EndX, int _FloorNum);
	AStair* FindStair(EStairType _StairType, int _FloorNum) const;
	FVector GetPlayerLocation() const;
	int GetPlayerFloorNum() const;

	void SetReplayStop();
	void SetReplay();
	void SetRewind();
	void ResetReplaySpeed();
	void IncreaseReplaySpeed();

	void PanicSwitchOn();
	void PanicSwitchOff();

	bool IsReplayEnd() const;
	bool IsRewindEnd() const;

	void BrightnessUp(float _DeltaTime);
	void BrightnessDown(float _DeltaTime);

	void BatterPartUpdate(float _AbilityTime);

	int FloorCheck(float _PosY);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
	
	virtual void LevelReStart() {};
	virtual void LevelReEnd();

	bool IsStageClear();
	bool IsRelayStart();
	virtual void ChangeStage() {};

protected:
	// Object
	std::shared_ptr<AMainCamera> MainCamera = nullptr;
	std::shared_ptr<AMouseAim> Aim = nullptr;
	std::shared_ptr<AColMapObject> ColMap = nullptr;

	std::shared_ptr<ADefaultPlayer> Player = nullptr;
	std::vector<std::shared_ptr<AEnemyBase>> AllEnemy;
	std::vector<std::shared_ptr<ARecMapCompoBase>> AllRecComponent;
	
	// UI
	std::shared_ptr<AGo> Go = nullptr;
	std::shared_ptr<AUp_HUD> HUD = nullptr;
	std::shared_ptr<AReplayUI> ReplayUI = nullptr;

	// Msg
	std::shared_ptr<AOutroMsg> OutroMsg = nullptr;
	std::shared_ptr<AFailedMsg> FailedMsg = nullptr;

	// Stage Info.
	float4 Brightness = float4::One;
	float4 EnemyBrightness = float4::One;
	bool BrightnessDownEnd = false;
	bool BrightnessUpEnd = false;
	float TotalPlayTime = 0.0f;
	float PlayTimeCount = 0.0f;
	int TotalEnemy = 0;

	std::vector<float> FloorY;
	std::vector<std::vector<std::shared_ptr<AStair>>> AllStair;
	std::vector<std::vector<std::shared_ptr<ADoor>>> AllDoor;

	// Effect
	std::shared_ptr<UGrayScaleEffect> GrayScaleEffect = nullptr;
	std::shared_ptr<UWaveEffect> WaveEffect = nullptr;
	std::shared_ptr<ADiamondTransition> DiaTransition = nullptr;

// 디버깅 관련
private:
	void Debug();
	void DebugMessageFunction();

// FSM
protected:
	UStateManager State;
	void StateInit();

	void IntroStart();
	void Intro(float _DeltaTime);

	void IntroEffectStart();
	void IntroEffect(float _DeltaTime);

	void IntroBigEffectStart();
	void IntroBigEffect(float _DeltaTime);

	void PlayStart();
	void Play(float _DeltaTime);

	virtual void ClearStart();
	void Clear(float _DeltaTime);

	void OutroStart();
	void Outro(float _DeltaTime);

	void ReplayStart();
	void Replay(float _DeltaTime);

	void PlayerDeadStart();
	void PlayerDead(float _DeltaTime);

	void RestartStart();
	void Restart(float _DeltaTime);

	void TransitionOnStart();
	void TransitionOn(float _DeltaTime);

	void TransitionOffStart();
	void TransitionOff(float _DeltaTime);

};

