#include "KZ_ShaderBase.hlsli"

// Vertex Shader //
struct UGrayScaleVSOuput
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

UGrayScaleVSOuput UGrayScaleEffect_VS(FKZ_Vertex _Input)
{
    UGrayScaleVSOuput Out = (UGrayScaleVSOuput) 0;
    Out.POSITION = _Input.POSITION;
    Out.TEXCOORD = _Input.TEXCOORD;
    return Out;
}

// Pixel Shader //
struct UGrayScalePSOuput
{
    float4 COLOR : SV_Target0;
};

TextureSet(Image, 0)

UGrayScalePSOuput UGrayScaleEffect_PS(UGrayScaleVSOuput _Input)
{
    UGrayScalePSOuput Out = (UGrayScalePSOuput) 0;
    
    float4 InputColor = Image.Sample(Image_Sampler, _Input.TEXCOORD.xy).rgba;
    
    float4 ResultColor = 0.0f;
    ResultColor.rgb = dot(InputColor.rgb, float3(0.3, 0.59, 0.11));
    ResultColor.a = InputColor.a;
    
    Out.COLOR.rgba = ResultColor.rgba;
    return Out;
}