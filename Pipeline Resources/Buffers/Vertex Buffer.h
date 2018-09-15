
#pragma once

//
//	VertexBuffer.h
//  Encapsulating a vertex buffer object
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Buffer Base.h"

namespace vxe {

	// a type of vertex
	template <typename T>
	class VertexBuffer : public BufferBase {

	public:
		using value_type = T;

		explicit VertexBuffer(_In_ ID3D11Device2* device, const T* vertices, int count,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned access = 0,
			unsigned flags = 0,
			unsigned stride = 0) : _vertexsize{ sizeof(T) }, BufferBase{ sizeof(T) * count }
		{
			DebugPrint(std::string("\t VertexBuffer<") + typeid(T).name() + std::string (">::Ctor ...\n"));
			DebugPrint(std::string("\t\t Vertex Size: ") + std::to_string(_vertexsize) + std::string("\n"));
			DebugPrint(std::string("\t\t Vertex Count: ") + std::to_string(count) + std::string("\n"));
			DebugPrint(std::string("\t\t Buffer Size: ") + std::to_string(_size) + std::string("\n"));

			//assert(_buffer != 0);

			CD3D11_BUFFER_DESC desc(_size, D3D11_BIND_VERTEX_BUFFER, usage, access, flags, stride);

			D3D11_SUBRESOURCE_DATA data = { 0 };
			data.pSysMem = vertices;

			// data.SysMemPitch = 0;
			// data.SysMemSlicePitch = 0;

			ThrowIfFailed(device->CreateBuffer(&desc, &data, &_buffer), __FILEW__, __LINE__);
		}

		void Bind(_In_ ID3D11DeviceContext2* context, unsigned slot, unsigned count, const unsigned offset)
		{
			//DebugPrint(std::string("\t VertexBuffer<") + typeid(T).name() + std::string(">::Bind() ...\n"));
			context->IASetVertexBuffers(slot, count, _buffer.GetAddressOf(), &_vertexsize, &offset);
		}

	private:
		unsigned _vertexsize;

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&&) = delete;

		VertexBuffer& operator= (const VertexBuffer&) = delete;
		VertexBuffer& operator= (VertexBuffer&&) = delete;
	};
}
