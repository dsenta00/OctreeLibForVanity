
#pragma once

//
//	Pyramids.h
//  Defining pyramids 
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\Mesh Base.h"

namespace vxe {

	template <typename T, typename U> class Pyramid : public MeshBase<T, U> { };

	template <>
	class Pyramid<DirectX::VertexPositionColor, unsigned short> : public MeshBase<DirectX::VertexPositionColor, unsigned short> {

	public:
		Pyramid() { }

		// Vertices are hardcoded
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t Pyramid<PositionColorVertex, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices = {
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f))
			};

			std::vector<unsigned short> indices = {
				0, 2, 1,
				1, 2, 3,
				0, 1, 4,
				1, 3, 4,
				3, 2, 4,
				2, 0, 4
			};

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Loading from a file
		virtual concurrency::task<void>LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t Pyramid<PositionNormalVertex, unsigned short>::LoadAsync() ...\n"));

			std::vector <DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Loading ...

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Creating from memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>& memory)
		{
			DebugPrint(std::string("\t Pyramid<VertexPositionColor, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}
	};

}