#pragma once
#include "PlayLevelBase.h"

// 설명 : Factory 1번째 스테이지
class AFactory_001 : public APlayLevelBase
{
	GENERATED_BODY(APlayLevelBase)
public:
	// constrcuter destructer
	AFactory_001();
	~AFactory_001();

	// delete Function
	AFactory_001(const AFactory_001& _Other) = delete;
	AFactory_001(AFactory_001&& _Other) noexcept = delete;
	AFactory_001& operator=(const AFactory_001& _Other) = delete;
	AFactory_001& operator=(AFactory_001&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

