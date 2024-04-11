#include "PreCompile.h"
#include "Level.h"
#include "GameMode.h"
#include "Renderer.h"
#include "Camera.h"
#include "EngineCore.h"
#include "EngineRenderTarget.h"

bool ULevel::IsActorConstructer = true;

ULevel::ULevel() 
{
	// MainCamera = std::make_shared<UCamera>();

	MainCamera = SpawnActor<UCamera>("MainCamera");
	UICamera = SpawnActor<UCamera>("NewActor");
	UICamera->InputOff();
}

ULevel::~ULevel() 
{
}

void ULevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	MainCamera->ViewPortSetting();
	GEngine->GetEngineDevice().BackBufferRenderTarget->Setting();
	
	MainCamera->CameraTransformUpdate();

	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& GroupRenderers = RenderGroup.second;

		for (std::shared_ptr<URenderer> Renderer : GroupRenderers)
		{
			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->RenderingTransformUpdate(MainCamera);
			Renderer->Render(_DeltaTime);
		}
	}
}

void ULevel::PushActor(std::shared_ptr<AActor> _Actor)
{
	if (nullptr == _Actor)
	{
		MsgBoxAssert("만들지 않은 액터를 추가하려고 했습니다.");
		return;
	}
	
	_Actor->SetWorld(this);
	_Actor->BeginPlay();

	Actors[_Actor->GetOrder()].push_back(_Actor);
}

void ULevel::ConstructorActor(std::shared_ptr<AActor> _Actor)
{
	_Actor->RootCheck();
}

void ULevel::PushRenderer(std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_Renderer->GetOrder()].push_front(_Renderer);
}

void ULevel::ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder)
{
	// 안지워지고 
	Renderers[_PrevOrder].remove(_Renderer);

	Renderers[_ChangeOrder].push_front(_Renderer);
}

void ULevel::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelStart(_NextLevel);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->LevelEnd(_NextLevel);
		}
	}
}
void ULevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->LevelStart(_PrevLevel);
		}
	}
}