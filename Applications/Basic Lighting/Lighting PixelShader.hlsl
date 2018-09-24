
//
//	Lighting PixelShader.hlsl
//  Defining a pixel shader calculating light
//
//	© 2015 Vanity DirectX 11.2 Engine(VXE).Zoraja Consulting d.o.o.All rights reserved.
//

#include "..\..\Library\Engine\Lighting\HLSL\Directional Light.hlsli"

cbuffer MaterialBuffer : register(b0)
{
	Material material;
};

cbuffer CameraPosition : register(b1)
{
	float3 Eye;
};

cbuffer DirectionalLightBuffer : register (b2)
{
	DirectionalLight directional;
};

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float3 worldposition : POSITION;
	float3 worldnormal : NORMAL;
};

float4 main(PixelShaderInput input) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it
	input.worldnormal = normalize(input.worldnormal);

	float3 tocamera = normalize(Eye - input.worldposition); 

	// Start with a sum of zero. 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 a, d, s;

	ComputeDirectionalLight(material, directional, input.worldnormal, tocamera, a, d, s);
	ambient += a;
	diffuse += d;
	specular += s;

	float4 color = ambient + diffuse + specular;

	// Common to take alpha from diffuse material.
	color.a = material.Diffuse.a;

	return color;
}