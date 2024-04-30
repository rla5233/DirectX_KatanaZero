#pragma once
#include "PlayLevelBase.h"

class AGangSter;

// 설명 : Factory 5번째 스테이지
class AFactory_005 : public APlayLevelBase
{
	GENERATED_BODY(APlayLevelBase)
public:
	// constrcuter destructer
	AFactory_005();
	~AFactory_005();

	// delete Function
	AFactory_005(const AFactory_005& _Other) = delete;
	AFactory_005(AFactory_005&& _Other) noexcept = delete;
	AFactory_005& operator=(const AFactory_005& _Other) = delete;
	AFactory_005& operator=(AFactory_005&& _Other) noexcept = delete;

	void ExtraGangsterOn();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;
	void LevelReEnd() override;

protected:
	void ChangeStage() override;

private:
	std::vector<AGangSter*> ExtraGangster;

// FSM	
protected:
	void ClearStart() override;

};

