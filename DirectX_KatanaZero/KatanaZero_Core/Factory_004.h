#pragma once

// ���� : Factory 4��° ��������
class AFactory_004 : public AGameMode
{
	GENERATED_BODY(AGameMode)
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

private:

};

