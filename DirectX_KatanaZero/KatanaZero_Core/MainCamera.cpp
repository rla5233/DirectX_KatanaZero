#include "PreCompile.h"
#include "MainCamera.h"

#include "PlayerBase.h"

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

	StateInit();
}

void AMainCamera::StateInit()
{
	// State Create
	State.CreateState(MainCameraState::chaseplayer);

	// State Start
	State.SetStartFunction(MainCameraState::chaseplayer,	std::bind(&AMainCamera::ChasePlayerStart, this));

	// State Update
	State.SetUpdateFunction(MainCameraState::chaseplayer,	std::bind(&AMainCamera::ChasePlayer, this, std::placeholders::_1));

}

void AMainCamera::ChasePlayerStart()
{
	ChasePlayer(0.0f);
}

void AMainCamera::ChasePlayer(float _DeltaTime)
{
	FVector Result = Player->GetActorLocation();

	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	FVector TexScale = MapTex->GetScale();

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

void AMainCamera::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}