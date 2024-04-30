#pragma once
#include <EngineCore/StateManager.h>

// 설명 : 클리어 AGo
class AGo : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AGo();
	~AGo();
	
	// delete Function
	AGo(const AGo& _Other) = delete;
	AGo(AGo&& _Other) noexcept = delete;
	AGo& operator=(const AGo& _Other) = delete;
	AGo& operator=(AGo&& _Other) noexcept = delete;

	void SetActorLocation(const FVector& _Pos);
	void AddActorLocation(const FVector& _Pos);

	inline void SetRepeatPos(const FVector& _Pos)
	{
		RepeatPos = _Pos;
	}

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	void Destroy()
	{
		Off();
		AActor::Destroy();
	}

	void On()
	{
		Go->SetActive(true);
		Arrow->SetActive(true);
	};

	void Off()
	{
		Go->SetActive(false);
		Arrow->SetActive(false);
	};

	void SetArrowDir(EEngineDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Init();

private:
	UStateManager State;

	void StateInit();

private:
	UImage* Go = nullptr;
	UImage* Arrow = nullptr;

	FVector RepeatPos = FVector::Zero;
	FVector Velocity = FVector::Zero;
	float MaxSpeed = 100.0f;
};

