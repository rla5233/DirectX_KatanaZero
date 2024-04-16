#pragma once

class AColMapObject;
class ADefaultPlayer;
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:
	std::shared_ptr<AColMapObject> ColMap = nullptr;
	std::shared_ptr<ADefaultPlayer> Player = nullptr;
	std::shared_ptr<AUp_HUD> HUD = nullptr;

private:
	void Debug();
	virtual void ResetPlayer() {};
	void DebugMessageFunction();

};

