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

	inline FVector GetAcc() const
	{
		return Acc;
	}

	inline void SetAcc(const FVector& _Acc)
	{
		Acc = _Acc;
	}

	inline void AddVelocity(const FVector& _Vel)
	{
		Velocity += _Vel;
	}

	inline void AddAcc(const FVector& _Acc)
	{
		Acc += _Acc;
	}

	void VelocityUpdate(float _DeltaTime)
	{
		Velocity += Acc * _DeltaTime;
	}

	void PosUpdate(AActor* _Actor, float _DeltaTime)
	{
		_Actor->AddActorLocation(Velocity * _DeltaTime);
	}

protected:


private:
	FVector Velocity = FVector::Zero;
	FVector Acc = FVector::Zero;

};

