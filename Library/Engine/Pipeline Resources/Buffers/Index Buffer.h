
#pragma once

//
//	Index Buffer.h
//  Encapsulating an index buffer object
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Buffer Base.h"

namespace vxe {

	// unsigned or short
	template <typename T>
	class IndexBuffer : public BufferBase {

	public:
		explicit IndexBuffer(_In_ ID3D11Device2 *device, void* indices, int count,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned access = 0,
			unsigned flags = 0,
			unsigned stride = 0) : _indexsize{ sizeof(T) }, BufferBase{ sizeof(T) * count }
		{
			DebugPrint(std::string("\t IndexBuffer<") + std::string(typeid(T).name()) + std::string(">::Ctor ...\n"));
			DebugPrint(std::string("\t\t Index Size: ") + std::to_string(sizeof(T)) + std::string("\n"));
			DebugPrint(std::string("\t\t Index Count: ") + std::to_string(count) + std::string("\n"));
			DebugPrint(std::string("\t\t Buffer Size: ") + std::to_string(_size) + std::string("\n"));

			//assert(_buffer != 0);

			CD3D11_BUFFER_DESC desc(_size, D3D11_BIND_INDEX_BUFFER, usage, access, flags, stride);

			D3D11_SUBRESOURCE_DATA data = { 0 };
			data.pSysMem = indices;

			//data.SysMemPitch = 0;
			//data.SysMemSlicePitch = 0;

			ThrowIfFailed(device->CreateBuffer(
				&desc, 
				&data, 
				_buffer.ReleaseAndGetAddressOf()), __FILEW__, __LINE__);
		}

		void Bind(_In_ ID3D11DeviceContext2* context, DXGI_FORMAT format, unsigned offset)
		{
			//DebugPrint(std::string("\t IndexBuffer<") + std::string(typeid(T).name()) + std::string(">::Bind() ...\n"));
			context->IASetIndexBuffer(_buffer.Get(), format, offset);
		}

	private:
		unsigned _indexsize;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer(IndexBuffer&&) = delete;

		IndexBuffer& operator= (const IndexBuffer&) = delete;
		IndexBuffer& operator= (IndexBuffer&&) = delete;
	};
}
