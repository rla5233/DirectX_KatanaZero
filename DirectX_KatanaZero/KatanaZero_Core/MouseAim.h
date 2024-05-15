#pragma once
#include <EngineCore/StateManager.h>

// 설명 : 마우스 커서 담당 클래스
class AMouseAim : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AMouseAim();
	~AMouseAim();
	
	// delete Function
	AMouseAim(const AMouseAim& _Other) = delete;
	AMouseAim(AMouseAim&& _Other) noexcept = delete;
	AMouseAim& operator=(const AMouseAim& _Other) = delete;
	AMouseAim& operator=(AMouseAim&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	static FVector GetMouseAimLocation()
	{
		return Location;
	}

	inline USpriteRenderer* GetBody() const
	{
		return Aim;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Aim = nullptr;

private:
	void StateInit();

	static FVector Location;
	UStateManager State;
};

