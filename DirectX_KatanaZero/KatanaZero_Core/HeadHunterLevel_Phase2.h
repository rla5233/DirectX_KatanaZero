#pragma once
#include "HeadHunterLevel.h"

class AGrenade;

// 설명 : HeadHunter 2페이즈
class AHeadHunterLevel_Phase2 : public AHeadHunterLevel
{
	GENERATED_BODY(AHeadHunterLevel)
public:
	// constrcuter destructer
	AHeadHunterLevel_Phase2();
	~AHeadHunterLevel_Phase2();

	// delete Function
	AHeadHunterLevel_Phase2(const AHeadHunterLevel_Phase2& _Other) = delete;
	AHeadHunterLevel_Phase2(AHeadHunterLevel_Phase2&& _Other) noexcept = delete;
	AHeadHunterLevel_Phase2& operator=(const AHeadHunterLevel_Phase2& _Other) = delete;
	AHeadHunterLevel_Phase2& operator=(AHeadHunterLevel_Phase2&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;
	void LevelReEnd() override;

private:
	std::vector<std::shared_ptr<AGrenade>> AllGrenade;
	const int GrenadeNum = 3;

};

