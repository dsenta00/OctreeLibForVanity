
//
//	Vertex Shader.hlsl
//  Defining a sample vertex shader
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

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : SV_Position;
	vector<float, 4> color : COLOR;
};

// Per-pixel color data passed through the pixel shader.
struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};

// Simple shader to do vertex processing on the GPU.
VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	float4 pos = float4(input.pos, 1.0f);

	// Transform the vertex position into projected space.
	pos = mul(pos, World);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	output.pos = pos;

	// Pass the color through without modification.
	output.color = input.color;

	return output;
}