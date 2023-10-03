
#include "common.hlsl"
struct MATRIXBUFFER
{
    matrix World;
    matrix View;
    matrix Projection;
};

// 行列類の定数バッファ
cbuffer Matrix0 : register(b0)
{
    MATRIXBUFFER matbuf;
}

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

void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(matbuf.World, matbuf.View);
	wvp = mul(wvp, matbuf.Projection);

	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse * Material.Diffuse;
}

