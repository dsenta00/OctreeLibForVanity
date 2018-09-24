

#pragma once

//
//	Triangles.h
//  Defining triangles 
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\Mesh Base.h"

namespace vxe {

	template <typename T, typename U> class Triangle : public MeshBase<T, U> {};

	template <>
	class Triangle<DirectX::VertexPositionColor, unsigned short> : public MeshBase<DirectX::VertexPositionColor, unsigned short>{

	public:
		Triangle() { }

		// Vertices are hardcoded
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t Triangle<PositionColorVertex, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices = {
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(0.0f, 0.866f, 0.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, -0.866f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, -0.866f, 0.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f))
			};

			std::vector<unsigned short> indices = { 0, 1, 2 };

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Loading from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t Triangle<PositionNormalVertex, unsigned short>::LoadAsync() ...\n"));

			std::vector <DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Loading ...

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>& data)
		{
			DebugPrint(std::string("\t Triangle<VertexPositionColor, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}
	};

}