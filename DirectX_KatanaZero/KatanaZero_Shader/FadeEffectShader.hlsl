#include "KatanaZeroShaderBase.hlsli"

struct FadeVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};





////////////////////////////////
cbuffer MatrixBuffer
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
};


// TYPEDEFS //
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


// Vertex Shader
PixelInputType FadeVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    // 행렬 연산을 하기 위해서는 벡터가 4개의 성분으로 되어 있어야 합니다.
    input.position.w = 1.0f;

    // 월드, 뷰, 프로젝션 행렬을 이용하여 대해 정점의 위치를 계산합니다.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // 픽셀 셰이더에서 사용할 텍스쳐의 좌표를 저장합니다.
    output.tex = input.tex;
    
    return output;
}


Texture2D shaderTexture;
SamplerState SampleType;

cbuffer FadeBuffer
{
    float fadeAmount;
    float3 padding;
};

// Pixel Shader
float4 FadePixelShader(PixelInputType input) : SV_TARGET
{
    float4 color;

    // 텍스쳐의 현재 위치 색상을 샘플링합니다.
    color = shaderTexture.Sample(SampleType, input.tex);
    
    // 색상의 밝기를 현재 페이드 퍼센트에 맞게 줄입니다.
    color = color * fadeAmount;

    return color;
}