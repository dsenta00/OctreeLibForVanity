
#pragma once

//
//	Constant Buffer.h
//  Encapsulating a constant buffer (a structure which size is multiple of 16 bytes)
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Buffer Base.h"

#include "..\..\Pipeline Stages\Shaders\Shader Base.h"

namespace vxe {

	template <typename T>
	class ConstantBuffer : public BufferBase {

	public:
		using value_type = T;

		explicit ConstantBuffer(_In_ ID3D11Device2* device,
			T* data = nullptr,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned access = 0,
			unsigned flags = 0,
			unsigned stride = 0) : BufferBase(16 * ((sizeof(T) + 15) / 16))
		{
			DebugPrint(std::string("\t ConstantBuffer<") + typeid(T).name() + std::string(">::Ctor ...\n"));
			DebugPrint(std::string("\t\t Buffer Size: ") + std::to_string(_size) + std::string("\n"));

			data = nullptr;

			//	assert(_buffer != 0);

			// For constant buffers the byte width must be multiple of 16 bytes
			// The maximum constant buffer size that is supported by shaders is 4096 128-bit constants
			CD3D11_BUFFER_DESC desc(_size, D3D11_BIND_CONSTANT_BUFFER, usage, access, flags, stride);

			ThrowIfFailed(device->CreateBuffer(
				&desc, 
				nullptr, 
				&_buffer), __FILEW__, __LINE__);
		}

		void Bind(_In_ ID3D11DeviceContext2* context, 
			ProgrammableStage shader = ProgrammableStage::VertexShaderStage,
			unsigned slot = 0, 
			unsigned count = 1)
		{
			//DebugPrint(std::string("\t ConstantBuffer<") + typeid(T).name() + std::string(">::Bind() ...\n"));

			//	A constant buffer can be bound to 6 pipeline locations
			//	TODO: See methods *SSet*Buffers1
			if (shader == ProgrammableStage::VertexShaderStage) {
				context->VSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else if (shader == ProgrammableStage::HullShaderStage) {
				context->HSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else if (shader == ProgrammableStage::DomainShaderStage) {
				context->DSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else if (shader == ProgrammableStage::GeometryShaderStage) {
				context->GSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else if (shader == ProgrammableStage::PixelShaderStage) {
				context->PSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else if (shader == ProgrammableStage::ComputeShaderStage) {
				context->CSSetConstantBuffers(slot, count, _buffer.GetAddressOf());
			}
			else
				return;
		}

		void Update(_In_ ID3D11DeviceContext2* context, const T& data, 
			unsigned subresource = 0, 
			const D3D11_BOX* box = nullptr, 
			unsigned rawpitch = 0, 
			unsigned depthpitch = 0)
		{
			//DebugPrint(std::string ("\t ConstantBuffer<") + typeid(T).name() + std::string(">::Update() ...\n"));

			context->UpdateSubresource(_buffer.Get(), subresource, box, &data, rawpitch, depthpitch);
		}

	private:
		ConstantBuffer(const ConstantBuffer&) = delete;
		ConstantBuffer(ConstantBuffer&&) = delete;

		ConstantBuffer& operator= (const ConstantBuffer&) = delete;
		ConstantBuffer& operator= (ConstantBuffer&&) = delete;
	};

}