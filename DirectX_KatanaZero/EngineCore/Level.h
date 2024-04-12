#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>
#include <set>
#include <map>



// final을 사용하면 이제 ULevel 상속받은 클래스를 만들수가 없어요.

// 설명 :
class AActor;
class UCamera;
class URenderer;
class AGameMode;
class UEngineCore;
class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend URenderer;
	friend UEngineCore;
	static bool IsActorConstructer;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	template<typename ActorType, typename EnumType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name, EnumType _Order)
	{
		return SpawnActor<ActorType>(_Name, static_cast<int>(_Order));
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name, int _Order = 0)
	{
		// 이 사이에서만 컴포넌트를 생성할수 있어야 한다.
		IsActorConstructer = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		ConstructorActor(NewActor, _Name, _Order);
		IsActorConstructer = false;

		PushActor(NewActor);


		return std::dynamic_pointer_cast<ActorType>(NewActor);
		// Actors[_Order].push_back(NewActor);
	}

	std::shared_ptr<UCamera> GetMainCamera()
	{
		return MainCamera;
	}

	template<typename EnumType>
	std::list<std::shared_ptr<AActor>> GetTickGroup(EnumType _Type)
	{
		return GetTickGroup(static_cast<int>(_Type));
	}

	// 복사. <= 부담이 만된다.
	std::list<std::shared_ptr<AActor>> GetTickGroup(int _Order)
	{
		return Actors[_Order];
	}


protected:
	void Tick(float _DeltaTime) override;
	void Render(float _DeltaTime);

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

private:
	std::shared_ptr<UCamera> MainCamera = nullptr;
	std::shared_ptr<UCamera> UICamera = nullptr;

	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	std::map<int, std::list<std::shared_ptr<URenderer>>> Renderers;

	void ConstructorActor(std::shared_ptr<AActor> _Actor, std::string_view _Name, int Order);
	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
	void ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder);

};

