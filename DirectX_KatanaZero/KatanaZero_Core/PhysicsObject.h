#pragma once

// 설명 : 물리 적용 오브젝트
class UPhysicsObject
{
public:
	// constrcuter destructer
	UPhysicsObject();
	~UPhysicsObject();

	// delete Function
	UPhysicsObject(const UPhysicsObject& _Other) = delete;
	UPhysicsObject(UPhysicsObject&& _Other) noexcept = delete;
	UPhysicsObject& operator=(const UPhysicsObject& _Other) = delete;
	UPhysicsObject& operator=(UPhysicsObject&& _Other) noexcept = delete;

	inline FVector GetVelocity() const
	{
		return Velocity;
	}

	inline void SetVelocity(const FVector& _Vel)
	{
		Velocity = _Vel;
	}

protected:


private:
	FVector Velocity = FVector::Zero;

};

