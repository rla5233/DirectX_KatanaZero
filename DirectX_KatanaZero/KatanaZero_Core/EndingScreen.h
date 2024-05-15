#pragma once

// Ό³Έν : EndingScreen
class AEndingScreen : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AEndingScreen();
	~AEndingScreen();
	
	// delete Function
	AEndingScreen(const AEndingScreen& _Other) = delete;
	AEndingScreen(AEndingScreen&& _Other) noexcept = delete;
	AEndingScreen& operator=(const AEndingScreen& _Other) = delete;
	AEndingScreen& operator=(AEndingScreen&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;

};

