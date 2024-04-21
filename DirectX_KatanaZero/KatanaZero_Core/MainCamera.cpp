#include "PreCompile.h"
#include "MainCamera.h"

AMainCamera::AMainCamera()
{
}

AMainCamera::~AMainCamera()
{
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	SetMainCamera();

	ULerpObject::SetActor(MainCamera);

}

void AMainCamera::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AMainCamera::PlayLevelChaseActor(std::shared_ptr<UEngineTexture> _MapTex, const FVector& _ActorPos)
{
	FVector Result = _ActorPos;

	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	FVector TexScale = _MapTex->GetScale();

	if (0.0f > Result.X - WinScale.hX())
	{
		Result.X = WinScale.hX();
	}

	if (TexScale.X < Result.X + WinScale.hX())
	{
		Result.X = TexScale.X - WinScale.hX();
	}

	if (0.0f > Result.Y - WinScale.hY())
	{
		Result.Y = WinScale.hY();
	}

	if (TexScale.Y < Result.Y + WinScale.hY())
	{
		Result.Y = TexScale.Y - WinScale.hY();
	}

	Result.Z = -100.0f;
	SetActorLocation(Result);
}