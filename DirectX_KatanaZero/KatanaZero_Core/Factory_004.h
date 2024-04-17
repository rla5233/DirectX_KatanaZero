#pragma once
#include "PlayLevelBase.h"

// 설명 : Factory 4번째 스테이지
class AFactory_004 : public APlayLevelBase
{
	GENERATED_BODY(APlayLevelBase)
public:
	// constrcuter destructer
	AFactory_004();
	~AFactory_004();

	// delete Function
	AFactory_004(const AFactory_004& _Other) = delete;
	AFactory_004(AFactory_004&& _Other) noexcept = delete;
	AFactory_004& operator=(const AFactory_004& _Other) = delete;
	AFactory_004& operator=(AFactory_004&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	void ResetPlayer() override;

};

