#include "PreCompile.h"
#include "CameraManager.h"

UCameraManager::UCameraManager()
{
}

UCameraManager::~UCameraManager()
{
}

void UCameraManager::ChaseActor(std::shared_ptr<UCamera> _MainCamera, const FVector& _ActorPos)
{
	FVector Result = FVector::Zero;
	FVector ActorPos = _ActorPos;
	Result = ActorPos;





	Result.Z = -100.0f;
	_MainCamera->SetActorLocation(Result);
}


