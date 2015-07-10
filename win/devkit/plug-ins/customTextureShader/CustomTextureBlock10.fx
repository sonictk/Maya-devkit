//-
// Copyright 2012 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
//+

RasterizerState RAST_FS
{
	CullMode = FRONT;
	FillMode = SOLID;
};


float4x4 wvp : WorldViewProjection < string UIWidget = "None"; >;

float colVal = {0};

Texture2D MyTexture
<
	string ResourceName = "";
	string UIName = "MyTexture";
	string ResourceType = "2D";
	string UIWidget = "FilePicker";
>;

SamplerState SAMP_MMMLWWW
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
};



struct APPDATA
{
	float3 Position : POSITION;
	float2 UVset0 : TEXCOORD0;
};

struct SHADERDATA
{
	float4 Position : SV_Position;
	float4 UVset0 : TEXCOORD0;
};


SHADERDATA ShaderVertex(APPDATA IN)
{
	SHADERDATA OUT;

	OUT.Position = float4(IN.Position, 1);

	float2 UVs = float2(IN.UVset0.x, 1.0f-IN.UVset0.y);
	float4 OutUVs = float4(UVs.x, UVs.y, 0, 0);
	OUT.UVset0 = OutUVs;

	float4 WVSpace = mul(OUT.Position, wvp);
	OUT.Position = WVSpace;

	return OUT;
}

// -------------------------------------- ShaderPixel --------------------------------------
struct PIXELDATA
{
	float4 Color : SV_Target;
};

PIXELDATA ShaderPixel(SHADERDATA IN)
{
	PIXELDATA OUT;

	float4 Sampler = MyTexture.Sample(SAMP_MMMLWWW, IN.UVset0.xy);
	float4 PixelColor = float4(Sampler.x, Sampler.y, Sampler.z, 1);
	OUT.Color = PixelColor + float4(colVal, 0, 0, 1);

	return OUT;
}

// -------------------------------------- technique11 Main ---------------------------------------
technique10 Main
{
	pass P0
	{
		SetRasterizerState(RAST_FS);
		SetVertexShader(CompileShader(vs_4_0, ShaderVertex()));
		SetPixelShader(CompileShader(ps_4_0, ShaderPixel()));
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetGeometryShader(NULL);
	}

}

