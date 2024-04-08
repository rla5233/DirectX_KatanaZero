
// 단순히 트랜스폼을 struct로 정의하는게 아니라.
// 상수버퍼라는것으로 선언해야 합니다.

// cbuffer 상수버퍼 쓰겠다.
// 상수버퍼는 16개까지 세팅이 가능하고
// b0 슬롯에 넣겠다.
// register(b15) 까지
// 하지만 상수버퍼에는 516kb이상이 되면 세팅이 불가능합니다.
// 크기에 제한이 있습니다.
cbuffer FTransform : register(b10)
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
};