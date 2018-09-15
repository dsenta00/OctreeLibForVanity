
//
//	Explicit Surface.h
//  Defining explicit sufraces
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\Utilities.h"
#include "Mesh Base.h"

namespace vxe {

	// unsigned short can be too small for all indices
	template <typename T, typename U> class ExplicitSurface : public MeshBase < T, U > { };

	template <>
	class ExplicitSurface<DirectX::VertexPositionColor, unsigned short> : public MeshBase<DirectX::VertexPositionColor, unsigned short>{

	private:
		float _width;
		float _depth;
		unsigned _m;
		unsigned _n;
		std::function<float(float, float)> _func;

	public:
		ExplicitSurface(float width, float depth, unsigned m, unsigned n, std::function<float(float, float)> func) :
			_width{ width },
			_depth{ depth },
			_m{ m },
			_n{ n },
			_func{ func }
		{ }

		// Vertices are hardcoded
		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device) override
		{
			DebugPrint(std::string("\t ExplicitSurface<VertexPositionColor, unsigned int>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			GenerateGeometry(vertices, indices);

			ApplyHeight(vertices);

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		// Loading from a file
		virtual concurrency::task<void> LoadAsync(_In_ ID3D11Device2* device, const std::wstring&) override
		{
			DebugPrint(std::string("\t ExplicitSurface<VertexPositionColor, unsigned int>::LoadAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Loading ...

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		virtual concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::vector<char>& data)
		{
			DebugPrint(std::string("\t ExplicitSurface<VertexPositionColor, unsigned>::CreateAsync() ...\n"));

			std::vector<DirectX::VertexPositionColor> vertices;
			std::vector<unsigned short> indices;

			// Extract (parse) vertices from memory

			return MeshBase::CreateAsync(device, vertices, indices);
		}

		void GenerateGeometry(std::vector<DirectX::VertexPositionColor>& vertices, std::vector<unsigned short>& indices) {

			unsigned vertexcount = _m * _n;
			unsigned facecount = 2 * (_m - 1) * (_n - 1);
			unsigned indexcount = 3 * facecount;

			vertices.resize(vertexcount);
			indices.resize(indexcount);

			float dx = _width / (_n - 1);
			float dz = _depth / (_m - 1);

			_width *= 0.5f;
			_depth *= 0.5f;

			//	Generating vertices (z, i, m, depth) (x, j, m, width)
			for (unsigned i = 0; i < _m; i++) {
				float z = _depth - i * dz;

				for (unsigned j = 0; j < _n; j++) {
					float x = -_width + j * dx;
					vertices[i*_n + j].position = DirectX::XMFLOAT3(x, 0.0f, z);
				}
			}

			//	Generating indices
			unsigned k = 0;
			for (unsigned i = 0; i < _m - 1; i++)
				for (unsigned j = 0; j < _n - 1; j++) {

					indices[k++] = i*_n + j;
					indices[k++] = i*_n + j + 1;
					indices[k++] = (i + 1)*_n + j;

					indices[k++] = (i + 1)*_n + j;
					indices[k++] = i*_n + j + 1;
					indices[k++] = (i + 1)*_n + j + 1;
				}
		}

		void ApplyHeight(std::vector<DirectX::VertexPositionColor>& vertices)
		{
			int count = (unsigned) vertices.size();

			for (int i = 0; i < count; i++) {
				vertices[i].position.y = _func(vertices[i].position.x, vertices[i].position.z);

				if (vertices[i].position.y < 0.0f)
					vertices[i].color = DirectX::XMFLOAT4(DirectX::Colors::DarkBlue);

				else if (vertices[i].position.y < 1.0f)
					vertices[i].color = DirectX::XMFLOAT4(DirectX::Colors::Blue);

				else if (vertices[i].position.y < 3.0f)
					vertices[i].color = DirectX::XMFLOAT4(DirectX::Colors::LawnGreen);

				else if (vertices[i].position.y < 4.5f)
					vertices[i].color = DirectX::XMFLOAT4(DirectX::Colors::Yellow);

				else if (vertices[i].position.y < 7.0f)
					vertices[i].color = DirectX::XMFLOAT4(DirectX::Colors::OrangeRed);

				else
					vertices[i].color = DirectX::XMFLOAT4(DirectX::Colors::DarkRed);

			}
		}
	};
}