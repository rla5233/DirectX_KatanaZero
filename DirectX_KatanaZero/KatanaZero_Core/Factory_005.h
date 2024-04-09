#pragma once

// 설명 : Factory 5번째 스테이지
class AFactory_005 : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AFactory_005();
	~AFactory_005();

	// delete Function
	AFactory_005(const AFactory_005& _Other) = delete;
	AFactory_005(AFactory_005&& _Other) noexcept = delete;
	AFactory_005& operator=(const AFactory_005& _Other) = delete;
	AFactory_005& operator=(AFactory_005&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:

};

