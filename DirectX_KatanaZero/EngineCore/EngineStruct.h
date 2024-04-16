#pragma once
#include <EngineBase/EngineMath.h>

struct FCuttingData
{
	//       0, 0
	float4 CuttingPosition;
	//      0.5 0.5
	float4 CuttingSize;
	float4x4 PivotMat;
};

struct ResultColorValue
{
	float4 PlusColor = float4::Zero;
	float4 MulColor = float4::One;
	float4 AlphaColor = float4::One;
};

