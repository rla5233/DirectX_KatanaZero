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
