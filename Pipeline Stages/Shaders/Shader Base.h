
#pragma once

//
//	Shader Base.h
//  A base class for shader objects
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

namespace vxe {

	enum class ProgrammableStage : byte {
		VertexShaderStage,
		HullShaderStage,
		DomainShaderStage,
		GeometryShaderStage,
		PixelShaderStage,
		ComputeShaderStage,
		Size
	};

	class ShaderBase  {

	public:
		ShaderBase() { }

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::wstring& filename) = 0;

		virtual void Bind(_In_ ID3D11DeviceContext2* context, ID3D11ClassInstance* const* instances, unsigned count) = 0;

		virtual void Reset() = 0;

		virtual ~ShaderBase() {}
	};

	inline std::string ToString(ProgrammableStage stage)
	{
		switch (stage) {

		default: return "What a #%@$";

		case ProgrammableStage::VertexShaderStage: return "VertexShaderStage";
		case ProgrammableStage::HullShaderStage: return "HullShaderStage";
		case ProgrammableStage::DomainShaderStage: return "DomainShaderStage";
		case ProgrammableStage::GeometryShaderStage: return "GeometryShaderStage";
		case ProgrammableStage::PixelShaderStage: return "PixelShaderStage";
		case ProgrammableStage::ComputeShaderStage: return "ComputeShaderStage";
		}
	}

}