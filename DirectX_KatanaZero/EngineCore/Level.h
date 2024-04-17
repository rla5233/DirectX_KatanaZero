#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>
#include <set>
#include <map>



// final�� ����ϸ� ���� ULevel ��ӹ��� Ŭ������ ������� �����.

// ���� :
class AActor;
class UCamera;
class URenderer;
class UCollision;
class AGameMode;
class UEngineCore;
class UWidget;
class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend URenderer;
	friend UCollision;
	friend UEngineCore;
	friend UWidget;
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
		// �� ���̿����� ������Ʈ�� �����Ҽ� �־�� �Ѵ�.
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

	std::shared_ptr<AGameMode> GetGameMode()
	{
		return GameMode;
	}

	template<typename EnumType>
	std::list<std::shared_ptr<AActor>> GetTickGroup(EnumType _Type)
	{
		return GetTickGroup(static_cast<int>(_Type));
	}

	// ����. <= �δ��� ���ȴ�.
	std::list<std::shared_ptr<AActor>> GetTickGroup(int _Order)
	{
		return Actors[_Order];
	}


protected:
	void Tick(float _DeltaTime) override;
	void Render(float _DeltaTime);

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

	void Destroy();

private:
	std::shared_ptr<UCamera> MainCamera = nullptr;
	std::shared_ptr<UCamera> UICamera = nullptr;

	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	std::map<int, std::list<std::shared_ptr<URenderer>>> Renderers;

	std::map<int, std::list<std::shared_ptr<UCollision>>> Collisions;

	// Widget�̶�� �Ҹ���
	// �ƿ� ���Ͷ� �и��Ǿ� �ִ�.
	std::map<int, std::list<std::shared_ptr<UWidget>>> Widgets;

	void ConstructorActor(std::shared_ptr<AActor> _Actor, std::string_view _Name, int Order);
	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
	void PushCollision(std::shared_ptr<UCollision> _Collision);
	void PushWidget(std::shared_ptr<UWidget> _Widget);
	void ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder);
	void ChangeOrderCollision(std::shared_ptr<UCollision> _Collision, int _PrevOrder, int _ChangeOrder);

	void SetGameMode(std::shared_ptr<AGameMode> _GameMode)
	{
		GameMode = _GameMode;
	}
};

