#pragma once
#include "PlayLevelBase.h"

// ���� : Factory 2��° ��������
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

private:
	void ResetPlayer() override;

};

