
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


struct LIGHT
{
    bool Enable;
    bool3 Dummy;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

// ライト定数バッファ
cbuffer LightBuffer : register(b2)
{
    LIGHT Light;
}


void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;
	wvp = mul(matbuf.World, matbuf.View);
	wvp = mul(wvp, matbuf.Projection);
	
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, matbuf.World);
	worldNormal = normalize(worldNormal);

	float d = - dot(Light.Direction.xyz, worldNormal.xyz);
	d = saturate(d);


	Out.Diffuse = In.Diffuse * Material.Diffuse * d * Light.Diffuse;
	Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
	Out.Diffuse += Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;


	Out.Diffuse.xyz = In.Diffuse.xyz * Material.Diffuse.xyz * d * Light.Diffuse.xyz;
	Out.Diffuse.xyz += In.Diffuse.xyz * Material.Ambient.xyz * Light.Ambient.xyz;
	Out.Diffuse.xyz += Material.Emission.xyz;
	Out.Diffuse.a = In.Diffuse.a* Material.Diffuse.a;

	Out.Position = mul( In.Position, wvp );
	Out.TexCoord = In.TexCoord;

}

