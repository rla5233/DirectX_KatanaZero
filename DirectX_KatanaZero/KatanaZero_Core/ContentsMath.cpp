#include "PreCompile.h"
#include "ContentsMath.h"

UContentsMath::UContentsMath()
{
}

UContentsMath::~UContentsMath()
{
}

/// <summary> X축 과의 각도 구하는 함수 (0 ~ 360) </summary>
float UContentsMath::GetAngleToX_2D(const FVector& _Dir)
{
	float Result = 0.0f;
	
	FVector dir = { _Dir.X, _Dir.Y, 0.0f };
	FVector x_axis = { 1.0f, 0.0f, 0.0f };

	float dot = float4::DotProduct3D(dir, x_axis);
	float dir_norm = GetVectorNorm(dir);
	float x_axis_norm = GetVectorNorm(x_axis);

	Result = acosf(dot / (dir_norm * x_axis_norm));

	FVector cross = float4::Cross3D(dir, x_axis);
	FVector n_vec = { 0.0f, 0.0f, 1.0f };
	if (0 < cross.Z * n_vec.Z)
	{
		Result = UEngineMath::PI2 - Result;
	}
	
	return Result * UEngineMath::RToD;
}



/// <summary> Vector의 길이를 구하는 함수 </summary>
float UContentsMath::GetVectorNorm(const FVector& _Vec)
{
	float Result = 0.0f;

	Result = sqrtf(powf(_Vec.X, 2) + powf(_Vec.Y, 2) + powf(_Vec.Z, 2));

	return Result;
}
