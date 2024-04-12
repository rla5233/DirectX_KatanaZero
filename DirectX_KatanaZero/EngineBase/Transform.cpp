#include "PreCompile.h"
#include "Transform.h"
#include "EngineDebug.h"


bool (*FTransform::CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CircleToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::CirCle)] = FTransform::RectToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::Rect)] = FTransform::CircleToRect;
	}
	~CollisionFunctionInit()
	{

	}
};

CollisionFunctionInit Inst;

bool FTransform::CircleToCircle(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.Sphere.Intersects(Right.Sphere);
}

bool FTransform::CircleToRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.Sphere.Intersects(Right.AABB);
}

bool FTransform::CircleToRotRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.Sphere.Intersects(Right.OBB);
}

bool FTransform::RectToCircle(const FTransform& _Left, const FTransform& _Right)
{
	return CircleToRect(_Right, _Left);
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.AABB.Intersects(Right.AABB);
}

bool FTransform::RotRectToRotRect(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	return Left.OBB.Intersects(Right.OBB);
}

bool FTransform::CircleToPoint(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	Right.Sphere.Radius = 0.0f;
	return Left.Sphere.Intersects(Right.Sphere);
}

bool FTransform::PointToCircle(const FTransform& _Left, const FTransform& _Right)
{
	return CircleToPoint(_Right, _Left);
}
bool FTransform::PointToRect(const FTransform& _Left, const FTransform& _Right)
{
	return RectToPoint(_Right, _Left);
}

bool FTransform::RectToPoint(const FTransform& _Left, const FTransform& _Right)
{
	CollisionData Left = _Left.GetCollisionData2D();
	CollisionData Right = _Right.GetCollisionData2D();
	Right.Sphere.Radius = 0.0f;
	return Left.AABB.Intersects(Right.Sphere);
}



FTransform::FTransform()
	: LocalScale(FVector::One)
	, LocalRotation(FVector::Zero)
	, LocalPosition(FVector::Zero)
{
}

FTransform::~FTransform()
{
}

bool FTransform::Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("���� �浹 �Լ��� ������ ���� �浹�Դϴ�");
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](*this, _Other);
}


void FTransform::TransformUpdate()
{
	//float4 Scale;
	//float4 Rotation;
	//float4 Position;
	//float4x4 ScaleMat;
	//float4x4 RotationMat;
	//float4x4 PositionMat;
	//float4x4 World;
	//float4x4 View;
	//float4x4 Projection;
	//float4x4 WVP;

	ScaleMat.Scale(LocalScale);

	RotationMat.RotationDeg(LocalRotation);

	PositionMat.Position(LocalPosition);

	LocalWorld = ScaleMat * RotationMat * PositionMat;
	World = LocalWorld * ParentMat;

	World.Decompose(WorldScale, WorldRotation, WorldPosition);

	// ���ʹϿ� ����
	WorldRotation = WorldRotation;

	// ũ * �� * �� => ����
	// ���� => ũ �� ��
	// World

	// �������� �Դϴ�.
}

void FTransform::CalculateViewAndProjection(FMatrix _View, FMatrix _Projection)
{
	View = _View;
	Projection = _Projection;
	WVP = World * _View * _Projection;
}