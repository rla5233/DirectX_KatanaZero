#pragma once
#include "PlayLevelBase.h"

// 설명 : Factory 3번째 스테이지
class AFactory_003 : public APlayLevelBase
{
	GENERATED_BODY(APlayLevelBase)
public:
	// constrcuter destructer
	AFactory_003();
	~AFactory_003();

	// delete Function
	AFactory_003(const AFactory_003& _Other) = delete;
	AFactory_003(AFactory_003&& _Other) noexcept = delete;
	AFactory_003& operator=(const AFactory_003& _Other) = delete;
	AFactory_003& operator=(AFactory_003&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	void ResetPlayer() override;

};

