#pragma once
#include <EngineCore/StateManager.h>
#include "LerpObject.h"

class APlayerBase;

struct FRetShakeRange
{
	float MinX = -15.0f;
	float MaxX = 15.0f;
	float MinY = -15.0f;
	float MaxY = 15.0f;
};

// ¼³¸í : ÄÜÅÙÃ÷ ¸ÞÀÎ Ä«¸Þ¶ó
class AMainCamera : public AActor, public ULerpObject
{
	GENERATED_BODY(AActor);
public:
	// constructor destructor
	AMainCamera();
	~AMainCamera();
	
	// delete Function
	AMainCamera(const AMainCamera& _Other) = delete;
	AMainCamera(AMainCamera&& _Other) noexcept = delete;
	AMainCamera& operator=(const AMainCamera& _Other) = delete;
	AMainCamera& operator=(AMainCamera&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline std::string GetCurState() const
	{
		return State.GetCurStateName();
	}

	inline void SetActorLocation(const FVector& _Pos)
	{
		MainCamera->SetActorLocation(_Pos);
	}

	inline FVector GetActorLocation()
	{
		return MainCamera->GetActorLocation();
	}

	inline void AddActorLocation(const FVector& _Pos)
	{
		MainCamera->AddActorLocation(_Pos);
	}

	inline void SetMapTex(UEngineTexture* _MapTex)
	{
		MapTex = _MapTex;
	}

	inline void SetPlayer(APlayerBase* _Player)
	{
		Player = _Player;
	}

	inline void SetRetShakePos(const FVector& _Pos)
	{
		RetShakePos = _Pos;
	}

	inline void SetRetShakeRange(const FRetShakeRange& _Range)
	{
		RetShakeRange = _Range;
	}

	inline void SetRetShakeTime(float _Time)
	{
		RetShakeTime = _Time;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	inline void SetMainCamera()
	{
		MainCamera = GetWorld()->GetMainCamera().get();
	}

	FVector MapRangeCheck(const FVector& _Pos);

private:
	UCamera* MainCamera = nullptr;
	UEngineTexture* MapTex = nullptr;
	APlayerBase* Player = nullptr;

	// RetShake
	FVector RetShakePos = FVector::Zero;
	FRetShakeRange RetShakeRange;
	float RetShakeTime = 0.3f;
	float RetShakeTimeCount = 0.0f;

	float TitleInTimeWeight = 2.0f;

private:
	UStateManager State;	
	void StateInit();
	
	void TitleInStart();
	void TitleIn(float _DeltaTime);

	void ChasePlayerStart();
	void ChasePlayer(float _DeltaTime);

	void ShakingStart();
	void Shaking(float _DeltaTime);	

	void RetShakingStart();
	void RetShaking(float _DeltaTime);

};

