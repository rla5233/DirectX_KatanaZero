#include "PreCompile.h"
#include "Level.h"
#include "GameMode.h"
#include "Renderer.h"
#include "Collision.h"
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
			// 액터는 존재하는게 중요하지 
			// 그리거나 충돌할때가 문제이기 때문에
			if (nullptr == Renderer->GetActor()->RootComponent)
			{
				MsgBoxAssert("루트컴포넌트가 지정되지 않은 액터가 있습니다" + Renderer->GetActor()->GetName());
				continue;
			}


			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->RenderingTransformUpdate(MainCamera);
			Renderer->Render(_DeltaTime);
		}
	}
}

void ULevel::Destroy()
{

	for (std::pair<const int, std::list<std::shared_ptr<UCollision>>>& Group : Collisions)
	{
		std::list<std::shared_ptr<UCollision>>& GroupCollisions = Group.second;

		std::list<std::shared_ptr<UCollision>>::iterator StartIter = GroupCollisions.begin();
		std::list<std::shared_ptr<UCollision>>::iterator EndIter = GroupCollisions.end();


		for (; StartIter != EndIter; )
		{
			std::shared_ptr<UCollision> CurCollision = *StartIter;

			if (false == CurCollision->GetActor()->IsDestroy())
			{
				++StartIter;
				continue;
			}

			StartIter = GroupCollisions.erase(StartIter);
		}
	}

	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& GroupRenderers = RenderGroup.second;

		std::list<std::shared_ptr<URenderer>>::iterator StartIter = GroupRenderers.begin();
		std::list<std::shared_ptr<URenderer>>::iterator EndIter = GroupRenderers.end();


		for (; StartIter != EndIter; )
		{
			std::shared_ptr<URenderer> CurRenderer = *StartIter;

			if (false == CurRenderer->GetActor()->IsDestroy())
			{
				++StartIter;
				continue;
			}

			StartIter = GroupRenderers.erase(StartIter);
		}
	}

	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		std::list<std::shared_ptr<AActor>>::iterator StartIter = GroupActors.begin();
		std::list<std::shared_ptr<AActor>>::iterator EndIter = GroupActors.end();

		for ( ; StartIter != EndIter; )
		{
			std::shared_ptr<AActor> CurActor = *StartIter;

			if (false == CurActor->IsDestroy())
			{
				++StartIter;
				continue;
			}

			CurActor->End();
			StartIter = GroupActors.erase(StartIter);
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

void ULevel::ConstructorActor(std::shared_ptr<AActor> _Actor, std::string_view _Name, int _Order)
{
	_Actor->SetName(_Name);
	_Actor->SetOrder(_Order);
}

void ULevel::PushRenderer(std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_Renderer->GetOrder()].push_front(_Renderer);
}

void ULevel::PushCollision(std::shared_ptr<UCollision> _Collision)
{
	Collisions[_Collision->GetOrder()].push_front(_Collision);
}

void ULevel::ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder)
{
	// 안지워지고 
	Renderers[_PrevOrder].remove(_Renderer);

	Renderers[_ChangeOrder].push_front(_Renderer);
}

void ULevel::ChangeOrderCollision(std::shared_ptr<UCollision> _Collision, int _PrevOrder, int _ChangeOrder)
{
	// 안지워지고 
	Collisions[_PrevOrder].remove(_Collision);

	Collisions[_ChangeOrder].push_front(_Collision);
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