#pragma once

// Ό³Έν :
class AHeadHunterGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AHeadHunterGameMode();
	~AHeadHunterGameMode();

	// delete Function
	AHeadHunterGameMode(const AHeadHunterGameMode& _Other) = delete;
	AHeadHunterGameMode(AHeadHunterGameMode&& _Other) noexcept = delete;
	AHeadHunterGameMode& operator=(const AHeadHunterGameMode& _Other) = delete;
	AHeadHunterGameMode& operator=(AHeadHunterGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

