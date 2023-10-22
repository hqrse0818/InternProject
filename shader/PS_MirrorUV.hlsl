#include "common.hlsl"

struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    bool TextureEnable;
    float2 Dummy;
};

// マテリアル定数バッファ
cbuffer MaterialBuffer : register(b1)
{
    MATERIAL Material;
}

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s1);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse;
    }
    else
    {
        outDiffuse = In.Diffuse;
    }
}
