#include "PreCompile.h"
#include "Collision.h"

UCollision::UCollision()
{
}

UCollision::~UCollision()
{
}

void UCollision::BeginPlay()
{
	// 한번 shared_ptr로 사용한 애들은 계속 shared_ptr로 사용하려고 ㅎ나다.
	// UCollision* Ptr = this;
	// std::shared_ptr<UCollision> Sptr = this;

	Super::BeginPlay();

	GetWorld()->PushCollision(shared_from_this());
}

void UCollision::SetCollisionGroup(int _Index)
{
	SetOrder(_Index);
}

bool UCollision::CollisionEnter(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function /*= nullptr*/)
{
	return Collision(_TargetGroup, _Function, nullptr, nullptr);
}

bool UCollision::CollisionStay(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function /*= nullptr*/)
{
	return Collision(_TargetGroup, nullptr, _Function, nullptr);

}

// 충돌이 끝났을때 1번
bool UCollision::CollisionExit(int _TargetGroup, std::function<void(std::shared_ptr<UCollision>)> _Function /*= nullptr*/)
{
	return Collision(_TargetGroup, nullptr, nullptr, _Function);
}

bool UCollision::Collision(int _TargetGroup,
	std::function<void(std::shared_ptr<UCollision>)> _Enter /*= nullptr*/,
	std::function<void(std::shared_ptr<UCollision>)> _Stay /*= nullptr*/,
	std::function<void(std::shared_ptr<UCollision>)> _Exit /*= nullptr*/)
{
	// Group 상대 그룹

	auto Test = GetWorld()->Collisions;

	std::list<std::shared_ptr<UCollision>>& Group = GetWorld()->Collisions[_TargetGroup];

	if (false == IsActive())
	{
		return false;
	}

	for (std::shared_ptr<UCollision> OtherCollision : Group)
	{
		ECollisionType ThisType = CollisionType;
		ECollisionType OtherType = OtherCollision->CollisionType;

		UCollision* CollisionPtr = OtherCollision.get();

		if (true == Transform.Collision(ThisType, OtherType, OtherCollision->Transform))
		{
			bool IsFirst = false;

			if (false == OtherCheck.contains(CollisionPtr))
			{
				IsFirst = true;
			}
			else {
				IsFirst = false;
			}

			if (nullptr != _Enter || nullptr != _Exit)
			{
				OtherCheck.insert(CollisionPtr);
			}

			if (true == IsFirst && nullptr != _Enter)
			{
				_Enter(OtherCollision);
			}
			else if (false == IsFirst && nullptr != _Stay)
			{
				_Stay(OtherCollision);
			}
		}
		else if (true == OtherCheck.contains(CollisionPtr) && nullptr != _Exit)
		{
			OtherCheck.erase(CollisionPtr);
			_Exit(OtherCollision);
		}
	}

	return false;
}

void UCollision::SetOrder(int _Order)
{
	// UTickObject::SetOrder(_Order);

	int PrevOrder = GetOrder();

	Super::SetOrder(_Order);

	if (nullptr != GetWorld())
	{
		GetWorld()->ChangeOrderCollision(shared_from_this(), PrevOrder, _Order);
	}
}
