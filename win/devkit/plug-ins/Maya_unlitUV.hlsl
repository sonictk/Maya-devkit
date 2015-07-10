/*******************************************************************************
 *
 * Maya_unlitUV
 *
 *******************************************************************************/

Texture2D diffuseTexture : register( t0 );
SamplerState diffuseSampler : register( s0 );

struct VS_INPUT
{
	float4 vertex : POSITION;
	float2 UV : TEXCOORD0;
};

struct PS_INPUT
{
	float4 position: SV_POSITION;
    float2 UV : TEXCOORD0;
};

cbuffer ConstantBuffer : register( b0 )
{
	matrix wvp : WorldViewProjection;
	float3 diffuseMaterial = float3( 0.8, 0.2, 0.0);
}

PS_INPUT mainVS( VS_INPUT In )
{ 
	PS_INPUT output = (PS_INPUT)0;
	output.position = mul( In.vertex, wvp);
	output.UV = In.UV;
	
	return output;
}

float4 mainPS(  PS_INPUT In ) : SV_Target
{
	float3 texColor = diffuseTexture.Sample(diffuseSampler, In.UV);

	float3 color = diffuseMaterial * texColor;
	//float3 color = texColor;
	//float3 color = float3( In.UV, 1.0f );
	return float4( color, 1.0);
}
