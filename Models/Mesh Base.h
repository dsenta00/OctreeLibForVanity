
#pragma once

//
//	Mesh Base.h
//  Defining an abstract representation of triangle lists 
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\Utilities.h"

#include "..\Third Party\DirectX Tool Kit\VertexTypes.h"

#include "..\Pipeline Resources\Buffers\Vertex Buffer.h"
#include "..\pipeline Resources\Buffers\Index Buffer.h"

namespace vxe {

	// T is a vertex type
	// U can be unsigned int or unsigned short 
	template <typename T, typename U> class MeshBase {

	public:
		using value_type1 = T;
		using value_type2 = U;

		MeshBase() : _vertexbuffer{ nullptr }, _indexbuffer{ nullptr }, _indexed{ false } { }

		concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device,
			std::vector<T>& vertices,
			std::vector<U>& indices,
			D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		{
			DebugPrint(std::string("\t MeshBase<") + typeid(T).name() + 
				std::string(",") + typeid(U).name() + std::string(">::CreateAsync() ...\n"));

			DebugPrint(std::string("\t\t Primitive Topology: ") + std::to_string(topology) + std::string("\n"));

			_topology = topology;
			_vertexcount = (unsigned int) vertices.size();
			_vertices = &vertices[0];

			return concurrency::create_task([this, device, vertices, indices]() {

				DebugPrint(std::string("\t -- A lambda: Creating a VB ... \n"));

				//	if (vertices.empty()) throw std::exception("...");

				_vertexbuffer = std::make_shared<VertexBuffer<T>>(device, &vertices[0], _vertexcount);

				if (!indices.empty()) {
					DebugPrint(std::string("\t -- A lambda: Creating an IB ... \n"));
					_indexed = true;

					_indexcount = (unsigned) indices.size();
					_indices = const_cast<U*> (&indices[0]);
					_indexbuffer = std::make_shared<IndexBuffer<U>>(device, violent_cast<void *> (&indices[0]), _indexcount);

					if (typeid(U) == typeid (unsigned short)) {
						_format = DXGI_FORMAT_R16_UINT;
						DebugPrint(std::string("\t\t Index Format: DXGI_FORMAT_R16_UINT \n"));
					}
					else {
						_format = DXGI_FORMAT_R32_UINT;
						DebugPrint(std::string("\t\t Index Format: DXGI_FORMAT_R32_UINT \n"));
					}
				}
			});
		}

		// Model is hardcoded inn memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) = 0;

		// Creation from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring& filename)
		{
			DebugPrint(std::string("\t MeshBase<") + typeid(T).name() + 
				std::string(",") + typeid(U).name() + std::string(">::CreateAsync()...\n"));

			_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			DebugPrint(std::string("\t\t Primitive Topology: ") + std::to_string(_topology) + std::string("\n"));

			return concurrency::create_task(DX::ReadDataAsync(filename)).then([this, device](const std::vector<byte> data)
			{
				DebugPrint(std::string("\t -- A lambda: Creating a VB and an IB ... \n"));

				unsigned char *p = const_cast<unsigned char*>(&data[0]);

				_vertexcount = *reinterpret_cast<unsigned int*>(p);
				_indexcount = *reinterpret_cast<unsigned int*>(p + sizeof(unsigned));

				_vertices = reinterpret_cast<T*>(p + 2 * sizeof(unsigned int));
				_indices = reinterpret_cast<U*>(p + 2 * sizeof(unsigned int) + sizeof(T) * _vertexcount);

				_vertexbuffer = std::make_shared<VertexBuffer<T>>(device, _vertices, _vertexcount);

				if (_indexcount != 0) {

					_indexed = true;
					_indexbuffer = std::make_shared<IndexBuffer<U>>(device, violent_cast<void *> (_indices), _indexcount);

					if (typeid(U) == typeid (unsigned short)) {
						_format = DXGI_FORMAT_R16_UINT;
						DebugPrint(std::string("\t\t Index Format: DXGI_FORMAT_R16_UINT \n"));
					}
					else {
						_format = DXGI_FORMAT_R32_UINT;
						DebugPrint(std::string("\t\t Index Format: DXGI_FORMAT_R32_UINT \n"));
					}
				}
				else {
					_indexed = false;
				}

				DebugPrint(std::string("\t -- A lambda: a VB and an IB are created. \n"));
			});
		}

		// Creation by parsing from memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>& memory) = 0;

		virtual void BindVertexBuffer(_In_ ID3D11DeviceContext2* context, 
			int slot = 0, 
			unsigned count = 1, 
			unsigned offset = 0)
		{
			/*DebugPrint(std::string("\t MeshBase<") + typeid(T).name() + 
				std::string(",") + typeid(U).name() + std::string(">::BindVertexBuffer() ...\n"));*/

			_vertexbuffer->Bind(context, slot, count, offset);
			context->IASetPrimitiveTopology(_topology);
		}

		virtual void BindIndexBuffer(_In_ ID3D11DeviceContext2* context, unsigned offset = 0)
		{
			/*DebugPrint(std::string("\t MeshBase<") + typeid(T).name() + std::string(",") + 
				typeid(U).name() + std::string(">::BindIndexBuffer() ...\n"));*/

			if (_indexed) _indexbuffer->Bind(context, _format, offset);
		}

		virtual void Draw(_In_ ID3D11DeviceContext2* context, unsigned start = 0)
		{
			context->Draw(_vertexcount, start);
		}

		virtual void DrawIndexed(_In_ ID3D11DeviceContext2* context, unsigned startindex = 0, unsigned startvertex = 0)
		{
			if (_indexed) context->DrawIndexed(_indexcount, startindex, startvertex);
		}

		T* GetVertices() { return _vertices; }
		unsigned GetVertexCount() { return _vertexcount; }

		void Reset()
		{
			DebugPrint(std::string("\t MeshBase<") + typeid(T).name() + std::string(",") + typeid(U).name() + std::string(">::Reset() ...\n"));

			_vertexbuffer->Reset();
			_indexbuffer->Reset();
		}

	protected:
		unsigned _vertexcount;
		std::shared_ptr<VertexBuffer<T>> _vertexbuffer;
		T* _vertices;

		bool _indexed;
		unsigned _indexcount;
		std::shared_ptr<IndexBuffer<U> > _indexbuffer;
		U* _indices;
		DXGI_FORMAT _format;

		D3D11_PRIMITIVE_TOPOLOGY _topology;
	};
}