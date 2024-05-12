#pragma once
#include <EngineCore/StateManager.h>

// Ό³Έν : HeadHunter2
class ALaser : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ALaser();
	~ALaser();
	
	// delete Function
	ALaser(const ALaser& _Other) = delete;
	ALaser(ALaser&& _Other) noexcept = delete;
	ALaser& operator=(const ALaser& _Other) = delete;
	ALaser& operator=(ALaser&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline void SetDeg(float _Deg)
	{
		Deg = _Deg;
	}

	inline void SetAlphaDownTimeCount(float _Time)
	{
		AlphaDownTimeCount = _Time;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;
	UCollision* BodyCol = nullptr;

	bool ShortShootUpdate = false;
	float AlphaDownTimeCount = 0.0f;
	float LaserAlpha = 1.0f;
	float Deg = 0.0f;

// FSM
private:
	UStateManager State;
	void StateInit();

};

