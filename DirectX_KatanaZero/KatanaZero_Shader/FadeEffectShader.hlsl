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
    
    // ��� ������ �ϱ� ���ؼ��� ���Ͱ� 4���� �������� �Ǿ� �־�� �մϴ�.
    input.position.w = 1.0f;

    // ����, ��, �������� ����� �̿��Ͽ� ���� ������ ��ġ�� ����մϴ�.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
    // �ȼ� ���̴����� ����� �ؽ����� ��ǥ�� �����մϴ�.
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

    // �ؽ����� ���� ��ġ ������ ���ø��մϴ�.
    color = shaderTexture.Sample(SampleType, input.tex);
    
    // ������ ��⸦ ���� ���̵� �ۼ�Ʈ�� �°� ���Դϴ�.
    color = color * fadeAmount;

    return color;
}