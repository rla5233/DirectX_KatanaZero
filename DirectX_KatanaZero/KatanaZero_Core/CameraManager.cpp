#include "PreCompile.h"
#include "CameraManager.h"

#include "ColMapObject.h"

UCameraManager::UCameraManager()
{
}

UCameraManager::~UCameraManager()
{
}

void UCameraManager::PlayLevelChaseActor(
	std::shared_ptr<UCamera> _MainCamera, 
	std::shared_ptr<UEngineTexture> MapTex,
	const FVector& _ActorPos)
{
	FVector Result = _ActorPos;

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
	_MainCamera->SetActorLocation(Result);
}