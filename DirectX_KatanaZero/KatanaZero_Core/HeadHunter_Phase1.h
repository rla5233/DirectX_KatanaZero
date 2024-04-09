#pragma once

// Ό³Έν :
class AHeadHunter_Phase1 : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AHeadHunter_Phase1();
	~AHeadHunter_Phase1();

	// delete Function
	AHeadHunter_Phase1(const AHeadHunter_Phase1& _Other) = delete;
	AHeadHunter_Phase1(AHeadHunter_Phase1&& _Other) noexcept = delete;
	AHeadHunter_Phase1& operator=(const AHeadHunter_Phase1& _Other) = delete;
	AHeadHunter_Phase1& operator=(AHeadHunter_Phase1&& _Other) noexcept = delete;

	protected:
		void BeginPlay()override;
		void Tick(float _DeltaTime) override;

private:

};

