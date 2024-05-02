#pragma once
#include <EngineCore/StateManager.h>
#include "LerpObject.h"

class APlayerBase;

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
	
	inline UCamera* GetMainCamera() const
	{
		return MainCamera;
	}

	inline void SetActorLocation(const FVector& _Pos)
	{
		MainCamera->SetActorLocation(_Pos);
	}

	inline FVector GetActorLocation()
	{
		MainCamera->GetActorLocation();
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCamera* MainCamera = nullptr;
	UEngineTexture* MapTex = nullptr;
	APlayerBase* Player = nullptr;

private:
	inline void SetMainCamera()
	{
		MainCamera = GetWorld()->GetMainCamera().get();
	}
	
private:
	UStateManager State;	
	void StateInit();
	
	void ChasePlayerStart();
	void ChasePlayer(float _DeltaTime);
};

