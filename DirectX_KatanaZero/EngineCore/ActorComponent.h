#pragma once
#include "Actor.h"
#include "TickObject.h"
#include <EngineBase/NameObject.h>
#include "WorldObject.h"

// 설명 : 그냥 소유만 당하는 애들이 있고
class UActorComponent : public UTickObject, public UNameObject, public UWorldObject
{
	friend AActor;

public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	bool IsActive()
	{
		return ActiveValue;
	}

	void SetActive(bool _Value)
	{
		ActiveValue = _Value;
	}

	AActor* GetActor()
	{
		return Actor;
	}


protected:

private:
	bool ActiveValue = true;

	AActor* Actor = nullptr;

	void SetActor(AActor* _Actor)
	{
		Actor = _Actor;
	}

};

