#pragma once
#include "PlayLevelBase.h"

class AHeadHunter;

// Ό³Έν : HeadHunter Level
class AHeadHunterLevel : public APlayLevelBase
{
	GENERATED_BODY(APlayLevelBase);
public:
	// constructor destructor
	AHeadHunterLevel();
	~AHeadHunterLevel();
	
	// delete Function
	AHeadHunterLevel(const AHeadHunterLevel& _Other) = delete;
	AHeadHunterLevel(AHeadHunterLevel&& _Other) noexcept = delete;
	AHeadHunterLevel& operator=(const AHeadHunterLevel& _Other) = delete;
	AHeadHunterLevel& operator=(AHeadHunterLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

protected:
	bool IsStageClear() override;

protected:
	std::shared_ptr<AHeadHunter> HeadHunter = nullptr;

};

