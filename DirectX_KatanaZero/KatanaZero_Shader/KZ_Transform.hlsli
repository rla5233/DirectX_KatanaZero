cbuffer FTransform : register(b10)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldPosition;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};


struct FTransform
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldPosition;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 PositionMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};


cbuffer FBaseRenderValue : register(b11)
{
    float AccTime;
    float Temp0;
    float ScreenX;
    float ScreenY;
};
