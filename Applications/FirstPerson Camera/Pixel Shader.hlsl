
//
//	Pixel Shader.hlsl
//  Defining a sample pixel shader
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	return float4 (1.0f, 1.0f, 0.0f, 1.0f);
}