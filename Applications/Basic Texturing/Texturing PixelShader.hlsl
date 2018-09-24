
//
//	Texturing PixelShader.hlsl
//  Defining a sample pixel shader for texturing
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

Texture2D Texture : register(t0);

SamplerState Sampler : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 norm : NORMAL;
	float2 tex : TEXCOORD0;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	// Light direction is hardcoded - it is relative to the world space
	float3 direction = normalize(float3(10, 0, 1));

	float4 color = Texture.Sample(Sampler, input.tex);
	//float4 color = {0.0f, 0.0f, 1.0f, 1.0f};

	float magnitude = 0.8f * saturate(dot(input.norm, -direction)) + 0.5f;

	return color * magnitude;
}