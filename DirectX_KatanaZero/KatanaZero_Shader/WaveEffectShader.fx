#include "KZ_ShaderBase.hlsli"

// Vertex Shader //
struct UWaveVSOuput
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

UWaveVSOuput UWaveEffect_VS(FKZ_Vertex _Input)
{
    UWaveVSOuput Out = (UWaveVSOuput) 0;
    Out.POSITION = _Input.POSITION;
    Out.TEXCOORD = _Input.TEXCOORD;
    return Out;
}

// Pixel Shader //
struct UWavePSOuput
{
    float4 COLOR : SV_Target0;
};

// Target BackBuffer
TextureSet(Image, 0)

// Pixel Shader// 
UWavePSOuput UWave_PS(UWaveVSOuput _Input)
{
    UWavePSOuput Out = (UWavePSOuput) 0;
    
    float2 TexPos = _Input.TEXCOORD.xy;
    
    float POWER = 0.06f;            // ÁÂ¿ì Èçµé¸²
    float VERTICAL_SPREAD = 4.0f;   // vertically
    float ANIM_SPEED = 0.6f;
    
    float y = (TexPos.y + AccTime * ANIM_SPEED) * VERTICAL_SPREAD;
    TexPos.x += (sin(y * 10.0f) * 0.2f) * POWER * sin(TexPos.y * 3.14f); // ¹è°æÂÊ Å« Èçµé¸² & ÀÜ ÁÖ¸§

    Out.COLOR.rgba = Image.Sample(Image_Sampler, TexPos).rgba;
    return Out;
}