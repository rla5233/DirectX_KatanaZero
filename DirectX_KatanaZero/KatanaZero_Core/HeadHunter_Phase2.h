#pragma once

// Ό³Έν :
class AHeadHunter_Phase2 : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AHeadHunter_Phase2();
	~AHeadHunter_Phase2();

	// delete Function
	AHeadHunter_Phase2(const AHeadHunter_Phase2& _Other) = delete;
	AHeadHunter_Phase2(AHeadHunter_Phase2&& _Other) noexcept = delete;
	AHeadHunter_Phase2& operator=(const AHeadHunter_Phase2& _Other) = delete;
	AHeadHunter_Phase2& operator=(AHeadHunter_Phase2&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

