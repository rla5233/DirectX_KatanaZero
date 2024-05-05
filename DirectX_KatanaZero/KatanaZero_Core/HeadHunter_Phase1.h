#pragma once
#include "HeadHunterLevel.h"

class ASlidingDoor;

// ���� : HeadHunter 1������
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

	void AllSlidingDoorClose();

protected:
	void BeginPlay()override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;

private:
	std::vector<std::shared_ptr<ASlidingDoor>> AllSlidingDoor;
	const int DoorNum = 4;

};

