#pragma once
#include "HeadHunterLevel.h"

class AGrenade;
class ABullet;

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

	void SetShootGrenade(
		const FVector& _ShootPos, 
		const FVector& _ShootDir, 
		float _Speed);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;
	void LevelReEnd() override;

private:
	void GrenadeIdxUpdate()
	{
		++CurGrenadeIdx;

		if (AllGrenade.size() <= CurGrenadeIdx)
		{
			CurGrenadeIdx = 0;
		}
	}

	void BulletIdxUpdate()
	{
		++CurBulletIdx;

		if (AllBullet.size() <= CurBulletIdx)
		{
			CurBulletIdx = 0;
		}
	}

private:
	std::vector<std::shared_ptr<AGrenade>> AllGrenade;
	const int GrenadeNum = 3;
	int CurGrenadeIdx = 0;

	std::vector<std::shared_ptr<ABullet>> AllBullet;
	const int BulletNum = 18;
	int CurBulletIdx = 0;

};

