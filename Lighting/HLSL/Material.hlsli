
#ifndef _MATERIAL_HLSLI_
#define _MATERIAL_HLSLI_

//
//	Material.hlsli
//  Defining a common code for metarial in shaders
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

struct Material {
	float4 Ambient;
	float4 Diffuse;
	float4 Specular; // w:power
	float4 Reflect;
};

#endif