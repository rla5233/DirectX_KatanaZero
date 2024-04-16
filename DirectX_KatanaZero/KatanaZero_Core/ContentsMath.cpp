#include "PreCompile.h"
#include "ContentsMath.h"

UContentsMath::UContentsMath()
{
}

UContentsMath::~UContentsMath()
{
}

float UContentsMath::GetAngleToX_2D(const FVector& _Dir)
{
	float Result = 0.0f;
	
	FVector dir = { _Dir.X, _Dir.Y, 0.0f };
	FVector x_axis = { 1.0f, 0.0f, 0.0f };

	float dot = float4::DotProduct3D(dir, x_axis);
	float dir_norm = GetVectorNorm(dir);
	float x_axis_norm = GetVectorNorm(x_axis);

	Result = acosf(dot / (dir_norm * x_axis_norm));

	FVector n_vec = { 0.0f, 0.0f, 1.0f };
	FVector cross = float4::Cross3D(dir, x_axis);

	if (0 < cross.Z * n_vec.Z)
	{
		Result = UEngineMath::PI2 - Result;
	}
	
	return Result * UEngineMath::RToD;
}

float UContentsMath::GetVectorNorm(const FVector& _Vec)
{
	float Result = 0.0f;

	Result = sqrtf(powf(_Vec.X, 2) + powf(_Vec.Y, 2) + powf(_Vec.Z, 2));

	return Result;
}
