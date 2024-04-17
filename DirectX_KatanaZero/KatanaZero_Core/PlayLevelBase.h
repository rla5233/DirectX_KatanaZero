#pragma once
#include <EngineCore/StateManager.h>

class AColMapObject;
class ADefaultPlayer;
class AEnemyBase;
class AMouseAim;
class AUp_HUD;

// 설명 : PlayLevel 기본 클래스
class APlayLevelBase : public AGameMode
{
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

	inline std::shared_ptr<AColMapObject> GetColMap() const
	{
		return ColMap;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	bool IsStageClear();

protected:
	std::shared_ptr<AMouseAim> Aim = nullptr;
	std::shared_ptr<AColMapObject> ColMap = nullptr;
	std::shared_ptr<ADefaultPlayer> Player = nullptr;
	std::shared_ptr<AUp_HUD> HUD = nullptr;
	std::vector<std::shared_ptr<AEnemyBase>> AllEnemy;

// FSM
private:
	UStateManager State;
	void StateInit();

	void Replay(float _DeltaTime);
	virtual void ChangeStage() {};

// 디버깅 관련
private:
	void Debug();
	virtual void ResetPlayer() {};
	void RestartCheck();
	void DebugMessageFunction();

};

