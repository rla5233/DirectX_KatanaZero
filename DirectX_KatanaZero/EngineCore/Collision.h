#pragma once
#include "SceneComponent.h"
#include <set>

// ���� : �浹ü Ŭ����
class UCollision : public USceneComponent, public std::enable_shared_from_this<UCollision>
{
	GENERATED_BODY(USceneComponent)

public:
	// constrcuter destructer
	UCollision();
	~UCollision();

	// delete Function
	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	template<typename EnumType>
	void SetCollisionGroup(EnumType _Index)
	{
		SetCollisionGroup(static_cast<int>(_Index));
	}

	void SetCollisionGroup(int _Index);

	// ���� �浹�� 1��
	template<typename EnumType>
	bool CollisionEnter(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionEnter(static_cast<int>(_TargetGroup), _Function);
	}

	bool CollisionEnter(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	// �ݸ��� �浹���̸� ���
	template<typename EnumType>
	bool CollisionStay(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionStay(static_cast<int>(_TargetGroup), _Function);
	}

	bool CollisionStay(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);
	
	// �浹�� ����� 1��
	template<typename EnumType>
	bool CollisionExit(EnumType _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr)
	{
		return CollisionExit(static_cast<int>(_TargetGroup), _Function);
	}

	bool CollisionExit(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function = nullptr);

	bool Collision(int _TargetGroup,
		std::function<void(std::shared_ptr<UCollision>)> _Enter = nullptr,
		std::function<void(std::shared_ptr<UCollision>)> _Stay = nullptr,
		std::function<void(std::shared_ptr<UCollision>)> _Exit = nullptr);

	void SetCollisionType(ECollisionType _CollisionType)
	{
		CollisionType = _CollisionType;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order) override;

	void SetActive(bool _Value) override
	{
		Super::SetActive(_Value);
		FirstCheck.clear();
		OtherCheck.clear();
		ExitCheck.clear();
	}

protected:
	void BeginPlay() override;
	void Tick(float _Delta) override;

private:
	ECollisionType CollisionType = ECollisionType::CirCle;

	std::set<UCollision*> FirstCheck;
	std::set<UCollision*> OtherCheck;
	std::set<UCollision*> ExitCheck;
};

