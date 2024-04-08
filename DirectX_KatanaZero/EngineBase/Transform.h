#pragma once
#include "EngineMath.h"

enum class ECollisionType
{
	Point,
	CirCle,
	Rect,
	Max,
};

// 설명 :
class CollisionFunctionInit;
struct FTransform
{
	float4 Scale;
	float4 Rotation;
	float4 Position;
	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 PositionMat;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 WVP;
	//};

	friend CollisionFunctionInit;

private:
	static bool (*CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

public:
	// constrcuter destructer
	FTransform();
	FTransform(const FVector& _Pos, const FVector& _Scale)
		: Position(_Pos), Scale(_Scale)
	{

	}
	~FTransform();

	// delete Function
	//FTransform(const FTransform& _Other) = delete;
	//FTransform(FTransform&& _Other) noexcept = delete;
	//FTransform& operator=(const FTransform& _Other) = delete;
	//FTransform& operator=(FTransform&& _Other) noexcept = delete;

	// bool CircleToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool CircleToCircle(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToRect(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool RectToCircle(const FTransform& _Left, const FTransform& _Right);


	static bool RectToPoint(const FTransform& _Left, const FTransform& _Right);

	static bool PointToRect(const FTransform& _Left, const FTransform& _Right);
	static bool PointToCircle(const FTransform& _Left, const FTransform& _Right);
public:
	void SetScale(FVector _Value)
	{
		Scale = _Value;
		TransformUpdate();
	}

	void SetRotationDeg(FVector _Value)
	{
		Rotation = _Value;
		TransformUpdate();
	}

	void SetPosition(FVector _Value)
	{
		Position = _Value;
		TransformUpdate();
	}

	void AddScale(FVector _Value)
	{
		SetScale(Scale + _Value);
	}

	FVector GetScale() const
	{
		return Scale;
	}

	void AddRotationDeg(FVector _Value)
	{
		SetRotationDeg(Rotation + _Value);
	}

	FVector GetRotation() const
	{
		return Rotation;
	}

	FVector GetForward()
	{
		return World.ArrVector[2].Normalize3DReturn();
	}

	FVector GetUp()
	{
		return World.ArrVector[1].Normalize3DReturn();
	}

	FVector GetRight()
	{
		return World.ArrVector[0].Normalize3DReturn();
	}

	FVector GetBack()
	{
		return -GetForward();
	}

	FVector GetDown()
	{
		return -GetUp();
	}

	FVector GetLeft()
	{
		return -GetRight();
	}


	void AddPosition(FVector _Value)
	{
		SetPosition(Position + _Value);
	}

	FVector GetPosition() const
	{
		return Position;
	}

	FVector LeftTop() const
	{
		return { Left(), Top() };
	}

	FVector RightTop() const
	{
		return { Right(), Top() };
	}

	FVector LeftBottom() const
	{
		return { Left(), Bottom() };
	}

	FVector RightBottom() const
	{
		return { Right(), Bottom() };
	}

	float Left() const
	{
		return Position.X - Scale.hX();
	}
	float Top() const
	{
		return Position.Y - Scale.hY();
	}
	float Right() const
	{
		return Position.X + Scale.hX();
	}
	float Bottom() const
	{
		return Position.Y + Scale.hY();
	}

	int iLeft() const
	{
		return std::lround(Left());
	}
	int iRight() const
	{
		return std::lround(Right());
	}
	int iTop() const
	{
		return std::lround(Top());
	}
	int iBottom() const
	{
		return std::lround(Bottom());
	}

	void SetRadius(float _Radius)
	{
		Scale = float4::Zero;
		Scale.X = _Radius * 2.0f;
	}

	float GetRadius() const
	{
		return Scale.hX();
	}

	// 충돌을 이녀석이 가질까?
	// 위치와 크기를 가지고 있기 때문에.
	bool Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other);

	void TransformUpdate();

	void CalculateViewAndProjection(FMatrix _View, FMatrix _Projection);

protected:

private:
};

