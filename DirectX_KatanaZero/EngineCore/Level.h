#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>



// final�� ����ϸ� ���� ULevel ��ӹ��� Ŭ������ ������� �����.

// ���� :
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

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string _Name, int _Order = 0)
	{
		// �� ���̿����� ������Ʈ�� �����Ҽ� �־�� �Ѵ�.
		IsActorConstructer = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		ConstructorActor(NewActor);
		IsActorConstructer = false;

		// ��
		//NewActor->SetWorld(this);
		//NewActor->BeginPlay();
		PushActor(NewActor);


		return std::dynamic_pointer_cast<ActorType>(NewActor);
		// Actors[_Order].push_back(NewActor);
	}

	std::shared_ptr<UCamera> GetMainCamera()
	{
		return MainCamera;
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

	void ConstructorActor(std::shared_ptr<AActor> _Actor);
	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
	void ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder);
	
};

