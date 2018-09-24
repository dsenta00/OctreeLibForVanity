
//
//	Lighting VertexShader.hlsl
//  Defining a sample vertex shader with lighting
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

cbuffer WorldTransforms : register(b0)
{
	matrix World;
	matrix Dlrow;
};

cbuffer ViewTransforms : register(b1)
{
	matrix View;
};

cbuffer ProjectionTransforms : register(b2)
{
	matrix Projection;
};

struct VertexShaderInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float3 worldposition : POSITION;
	float3 worldnormal : NORMAL;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;

	// Transform to world space 
	output.worldposition = mul(float4(input.position, 1.0f), World).xyz;
	output.worldnormal = mul(input.normal, (float3x3)Dlrow);

	// Transform to clip space 
	float4 pos = float4(input.position, 1.0f);
	pos = mul(pos, World);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	output.position = pos;

	return output;
}