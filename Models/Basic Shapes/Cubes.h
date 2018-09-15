
#pragma once

//
//	Cubes.h
//  Defining cubes 
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\Mesh Base.h"

namespace vxe {

	template <typename T, typename U> class Cube : public MeshBase<T, U> {};

	template <>
	class Cube<DirectX::VertexPositionColor, unsigned short> : public MeshBase<DirectX::VertexPositionColor, unsigned short>{

	public:
		Cube() {}

		// Vertices are hardcoded
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t Cube<PositionColorVertex, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices = {
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)),
				DirectX::VertexPositionColor(DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f))
			};

			std::vector<unsigned short> indices = {
				3, 1, 0,
				2, 1, 3,
				0, 5, 4,
				1, 5, 0,
				3, 4, 7,
				0, 4, 3,
				1, 6, 5,
				2, 6, 1,
				2, 7, 6,
				3, 7, 2,
				6, 4, 5,
				7, 4, 6,
			};

			return MeshBase::CreateAsync(device, vertices, indices, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		// Loading from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t Cube<VertexPositionColor, unsigned short>::LoadAsync() ...\n"));

			std::vector <DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Loading ...

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Creating from memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>&)
		{
			DebugPrint(std::string("\t Cube<VertexPositionColor1, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}	
	};


	template <>
	class Cube<DirectX::VertexPositionNormal, unsigned short> : public MeshBase <DirectX::VertexPositionNormal, unsigned short >{

	public:
		Cube() {}

		// Vertices are hardcoded
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t Cube<VertexPositionNormal, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionNormal> vertices = {

				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)),		// Side +z
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)),

				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)),    // Side -z
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)),

				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)),		// Side +y
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)),

				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)),	// Side -y
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)),

				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)),		// Side +x
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)),

				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)),	// Side -x
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)),
				DirectX::VertexPositionNormal(DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)),
			};

			std::vector<unsigned short> indices = {
				0, 1, 2,		// side 1
				2, 1, 3,
				4, 5, 6,		// side 2
				6, 5, 7,
				8, 9, 10,		// side 3
				10, 9, 11,
				12, 13, 14,		// side 4
				14, 13, 15,
				16, 17, 18,		// side 5
				18, 17, 19,
				20, 21, 22,		// side 6
				22, 21, 23,
			};

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Loading from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t Cube<VertexPositionNormal, unsigned short>::LaodAsync() ...\n"));

			std::vector <DirectX::VertexPositionNormal> vertices;
			std::vector<unsigned short> indices;

			// Loading from a file

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Creating from memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>&)
		{
			DebugPrint(std::string("\t Cube<VertexPositionNormal, unsigned short>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionNormal> vertices;
			std::vector<unsigned short> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}
	};
	template <>
	class Cube<DirectX::VertexPositionNormalTexture, unsigned short> : public MeshBase<DirectX::VertexPositionNormalTexture, unsigned short>{

	public:
		Cube() {}

		// Vertices are hardcoded
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t Cube<VertexPositionNormalTexture, unsigned short>::CreateAsync() ...\n"));

			// Right-handed
			std::vector<DirectX::VertexPositionNormalTexture> vertices = {

				// +Y (top face)
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

				// -Y (bottom face)
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

				// +X (right face)
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

				// -X (left face)
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

				// +Z (front face)
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

				// -Z (back face)
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
				DirectX::VertexPositionNormalTexture{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }
			};

			std::vector<unsigned short> indices = {
				0, 1, 2,
				0, 2, 3,
				4, 5, 6,
				4, 6, 7,
				8, 9, 10,
				8, 10, 11,
				12, 13, 14,
				12, 14, 15,
				16, 17, 18,
				16, 18, 19,
				20, 21, 22,
				20, 22, 23
			};

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Loading from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t Cube<VertexPositionNormalTexture, unsigned short>::CreateAsync() ...\n"));

			std::vector <DirectX::VertexPositionNormalTexture> vertices;
			std::vector<unsigned short> indices;

			// Loading from a file

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Creating from memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>&)
		{
			DebugPrint(std::string("\t Cube<VertexPositionNormalTexture, unsigned>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionNormalTexture> vertices;
			std::vector<unsigned short> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}
	};
}