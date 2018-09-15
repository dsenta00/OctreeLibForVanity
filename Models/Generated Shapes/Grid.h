
//
//	Grid.h
//  Defining a X-Z grid (plane)
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\Mesh Base.h"

namespace vxe {

	// unsigned short can be too small for all indices
	template <typename T, typename U> class Grid : public MeshBase < T, U > { };

	template <>
	class Grid<DirectX::VertexPositionNormalTangentTexture, unsigned int> : public MeshBase<DirectX::VertexPositionNormalTangentTexture, unsigned int>{

	private:
		float _width;
		float _depth;
		unsigned _m;
		unsigned _n;

	public:
		Grid(float width, float depth, unsigned m, unsigned n) :
			_width{ width },
			_depth{ depth },
			_m{ m },	// The number of vertices in x
			_n{ n }		// The number of vertices in z
		{ }

		// Vertices are generated
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t Grid<VertexPositionNormalTangentTexture, unsigned int>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionNormalTangentTexture> vertices;
			std::vector<unsigned int> indices;

			GenerateGeometry(vertices, indices);

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Loading from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t Grid<VertexPositionColor, unsigned int>::LoadAsync() ...\n"));

			std::vector<DirectX::VertexPositionNormalTangentTexture> vertices;
			std::vector<unsigned int> indices;

			// Loading ...

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Creating from memory
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>& data)
		{
			DebugPrint(std::string("\t Grid<VertexPositionColor, unsigned int>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionNormalTangentTexture> vertices;
			std::vector<unsigned int> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		void GenerateGeometry(std::vector<DirectX::VertexPositionNormalTangentTexture>& vertices, std::vector<unsigned int>& indices)
		{
			DebugPrint(std::string("\t Grid<VertexPositionNormalTangentTexture, unsigned int>::CreateAsync() ...\n"));

			unsigned vertexcount = _m * _n;
			unsigned quadcount = (_m - 1) * (_n - 1);
			unsigned facecount = 2 * quadcount;

			DebugPrint(std::string("\t\t Vertex Count: " + std::to_string(vertexcount)) + "\n");
			DebugPrint(std::string("\t\t Face Count: " + std::to_string(facecount)) + "\n");

			vertices.resize(vertexcount);

			float dx = _width / (_n - 1);
			float dz = _depth / (_m - 1);

			float du = 1.0f / (_n - 1);
			float dv = 1.0f / (_m - 1);

			float halfwidth = _width * 0.5f;
			float halfdepth = _depth * 0.5f;

			for (unsigned i = 0; i < _m; i++) {

				float z = halfdepth - i * dz;

				for (unsigned j = 0; j < _n; j++) {

					float x = -halfwidth + j * dx;
					vertices[i*_n + j].position = DirectX::XMFLOAT3(x, 0.0f, z);

					vertices[i*_n + j].normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
					vertices[i*_n + j].tangent = DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f);

					vertices[i*_n + j].textureCoordinate.x = j * du;
					vertices[i*_n + j].textureCoordinate.y = i * dv;
				}
			}

			unsigned indexcount = 3 * facecount;
			indices.resize(indexcount);

			//	Generating faces from quads
			unsigned k = 0;
			for (unsigned i = 0; i < _m - 1; i++)
				for (unsigned j = 0; j < _n - 1; j++) {

					// the first triangle
					indices[k++] = i*_n + j;
					indices[k++] = i*_n + j + 1;
					indices[k++] = (i + 1)*_n + j;

					// The second triangle
					indices[k++] = (i + 1)*_n + j;
					indices[k++] = i*_n + j + 1;
					indices[k++] = (i + 1)*_n + j + 1;
				}
		}
	};
}