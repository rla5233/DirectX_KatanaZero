#pragma once
#include "LerpObject.h"

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

	UCamera* GetMainCamera() const
	{
		return MainCamera;
	}

	void SetActorLocation(const FVector& _Pos)
	{
		MainCamera->SetActorLocation(_Pos);
	}

	FVector GetActorLocation()
	{
		MainCamera->GetActorLocation();
	}

	void AddActorLocation(const FVector& _Pos)
	{
		MainCamera->AddActorLocation(_Pos);
	}

	void PlayLevelChaseActor(std::shared_ptr<UEngineTexture> _MapTex, const FVector& _ActorPos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCamera* MainCamera = nullptr;

	void SetMainCamera()
	{
		MainCamera = GetWorld()->GetMainCamera().get();
	}
};

