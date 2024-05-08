#pragma once
#include "HeadHunterLevel.h"

class ASlidingDoor;
class AUnderBlack;
class AMine;

// 설명 : HeadHunter 1페이즈
class AHeadHunter_Phase1 : public AHeadHunterLevel
{
	GENERATED_BODY(AHeadHunterLevel)
public:
	// constrcuter destructer
	AHeadHunter_Phase1();
	~AHeadHunter_Phase1();

	// delete Function
	AHeadHunter_Phase1(const AHeadHunter_Phase1& _Other) = delete;
	AHeadHunter_Phase1(AHeadHunter_Phase1&& _Other) noexcept = delete;
	AHeadHunter_Phase1& operator=(const AHeadHunter_Phase1& _Other) = delete;
	AHeadHunter_Phase1& operator=(AHeadHunter_Phase1&& _Other) noexcept = delete;

	FVector FindExitDoor() override;

	void AllSlidingDoorClose();
	void AllMineOn();

protected:
	void BeginPlay()override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;
	void LevelReEnd() override;

	bool IsStageClear() override;
	void ChangeStage() override;

private:
	std::vector<std::shared_ptr<ASlidingDoor>> AllSlidingDoor;
	const int SlidingDoorNum = 4;

	std::vector<std::shared_ptr<AMine>> AllMine;
	const float MineInterVal = 40.0f;
	const int MineNum = 32;

	std::vector<float> DoorPosX = { 222.0f, 504.0f, 860.0f, 1126.0f };

	std::shared_ptr<AUnderBlack> UnderBlack = nullptr;

// FSM
private:
	void ClearStart() override;
	void Clear(float _DeltaTime) override;
};

