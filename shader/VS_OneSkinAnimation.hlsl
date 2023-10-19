struct VS_IN
{
    float4 Pos : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
    int4 BoneIdx : BONEINDEX;
    float4 BoneWeight : BONEWEIGHT;
};

struct PS_IN
{
    float4 Pos : SV_Position;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

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

// ボーン定数バッファ
cbuffer BoneMatBuf : register(b3)
{
    matrix Bonemtx[400];
}

cbuffer ScaleBuf : register(b4)
{
    float4 sc;
}

PS_IN main(VS_IN vin)
{
    PS_IN pout;
    
    // ワンスキン頂点ブレンドの処理
    float4x4 comb = (float4x4) 0;
    for (int i = 0; i < 4; i++)
    {
		// 重みを計算しながら行列生成
        comb += Bonemtx[vin.BoneIdx[i]] * vin.BoneWeight[i];
    }

    float4 Pos;
    
    Pos = mul(comb, vin.Pos);
    
    Pos.xyz *= sc.xyz;
    vin.Pos = Pos;

	// 
    matrix wvp;
    wvp = mul(matbuf.World, matbuf.View);
    wvp = mul(wvp, matbuf.Projection);
	
    float4 worldNormal, normal;
    normal = float4(vin.Normal.xyz, 0.0);
    worldNormal = mul(normal, matbuf.World);
    worldNormal = normalize(worldNormal);
    
    pout.Pos = mul(vin.Pos, wvp);
    
    float d = -dot(Light.Direction.xyz, worldNormal.xyz);
    d = saturate(d);
    
    pout.Diffuse = vin.Diffuse * Material.Diffuse * d * Light.Diffuse;
    pout.Diffuse += vin.Diffuse * Material.Ambient * Light.Ambient;
    pout.Diffuse += Material.Emission;
    pout.Diffuse.a = vin.Diffuse.a * Material.Diffuse.a;
    
    pout.Diffuse.xyz = vin.Diffuse.xyz * Material.Diffuse.xyz * d * Light.Diffuse.xyz;
    pout.Diffuse.xyz += vin.Diffuse.xyz * Material.Ambient.xyz * Light.Ambient.xyz;
    pout.Diffuse.xyz += Material.Emission.xyz;
    pout.Diffuse.a = vin.Diffuse.a * Material.Diffuse.a;
    
    pout.TexCoord = vin.TexCoord;
    
	return pout;
}