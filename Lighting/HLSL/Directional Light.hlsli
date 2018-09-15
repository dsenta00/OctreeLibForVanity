
#ifndef _DIRECTIONALLIGHT_HLSLI_
#define _DIRECTIONALLIGHT_HLSLI_

//
//	DirectionalLight.hlsli
//  Defining a common code for directional lighting in shaders
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "Material.hlsli"

struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float Padding;
};

void ComputeDirectionalLight(Material M, DirectionalLight L, float3 n, float3 v, out float4 ambient, out float4 diffuse, out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The light vector ia opposite to the incidentvector
	float3 l = -L.Direction;

		// Component-wise multiplication
		ambient = L.Ambient * M.Ambient;

	float k = dot(l, n);

	[flatten]
	if (k > 0.0f) {
		// the reflection vector
		float3 r = reflect(-l, n);
			float s = pow(max(dot(r, v), 0.0f), M.Specular.w);

		diffuse = k * M.Diffuse * L.Diffuse;
		specular = s * M.Specular * L.Specular;
	}
}

#endif