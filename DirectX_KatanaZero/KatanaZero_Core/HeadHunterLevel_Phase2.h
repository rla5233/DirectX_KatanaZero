#pragma once
#include "HeadHunterLevel.h"

class AWallTurret;
class AGrenade;
class ABullet;
class AHeadHunterHead;

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

	void SetShootGrenade(const FVector& _ShootPos, const FVector& _ShootDir, float _Speed);
	void SetShootBullet(const FVector& _ShootPos, const FVector& _ShootDir);
	void SetWallTurret();
	void SetHeadHunterHead(const FVector& _Pos, EEngineDir _Dir);

	void CreateLaser(const FVector& _Pos, float _Deg, float _AlphaDownDelayTime = 0.0f);

	static int GetBulletNum()
	{
		return BulletNum;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;
	void LevelReEnd() override;

	void RestartStart() override;

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

	void EndingFadeOut(float _DeltaTime);

private:
	std::vector<std::shared_ptr<AGrenade>> AllGrenade;
	const int GrenadeNum = 3;
	int CurGrenadeIdx = 0;

	std::vector<std::shared_ptr<ABullet>> AllBullet;
	static const int BulletNum;
	int CurBulletIdx = 0;

	std::shared_ptr<AWallTurret> WallTurret = nullptr;
	std::shared_ptr<AHeadHunterHead> HeadHunterHead = nullptr;

	float EndingFadeOutAlpha = 1.0f;
	bool IsEndingFadeOut = false;

// FSM
private:
	void ClearStart() override;
	void Clear(float _DeltaTime) override;

};

