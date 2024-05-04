#pragma once
#include "PlayLevelBase.h"

class AFactoryIntroUI;

// 설명 : Factory 2번째 스테이지
class AFactory_002 : public APlayLevelBase
{
	GENERATED_BODY(APlayLevelBase)
public:
	// constrcuter destructer
	AFactory_002();
	~AFactory_002();

	// delete Function
	AFactory_002(const AFactory_002& _Other) = delete;
	AFactory_002(AFactory_002&& _Other) noexcept = delete;
	AFactory_002& operator=(const AFactory_002& _Other) = delete;
	AFactory_002& operator=(AFactory_002&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void LevelReStart() override;

protected:
	void ChangeStage() override;

private:
	std::shared_ptr<AFactoryIntroUI> IntroUI = nullptr;

// FSM	
protected:
	void ClearStart() override;

};

