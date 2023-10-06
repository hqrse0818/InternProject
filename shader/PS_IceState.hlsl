#include "common.hlsl"

cbuffer Col : register(b2)
{
    float4 col;
}

float4 main(PS_IN pin) : SV_TARGET
{
	return col;
}