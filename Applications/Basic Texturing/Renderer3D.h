
#pragma once

//
//	Renderer3D.h
//  Defining a 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\..\Library\Engine\Third Party\DirectX Tool Kit\VertexTypes.h"
#include "..\..\..\Library\Engine\Models\Mesh Base.h"

#include "..\..\..\Library\Engine\Pipeline Stages\Shaders\Vertex Shader.h"
#include "..\..\..\Library\Engine\Pipeline Stages\Shaders\Pixel Shader.h"

#include "..\..\..\Library\Engine\Scene\Transforms\World Transforms.h"
#include "..\..\..\Library\Engine\Scene\Transforms\View Transform.h"
#include "..\..\..\Library\Engine\Scene\Transforms\Projection Transform.h"

#include "..\..\..\Library\Engine\Pipeline Resources\Textures\Texture2D.h"

namespace vxe
{
	class Renderer3D : public RendererBase3D {

	public:
		Renderer3D::Renderer3D() : RendererBase3D()
		{
			DebugPrint(std::string("\t Renderer3D::Ctor... \n"));
		}

		virtual void CreateDeviceDependentResources() override;
		virtual void CreateWindowSizeDependentResources() override;
		virtual void ReleaseDeviceDependentResources() override;

		virtual void Render() override;

		void SetTexturing();

		void Rotate(float radians) override
		{
			_world->RotateY(radians);
		}

	private:
		void SetCamera()
		{
			auto context = m_deviceResources->GetD3DDeviceContext();

			_view->GetConstantBuffer()->Bind(context, ProgrammableStage::VertexShaderStage, 1);

			_projection->GetConstantBuffer()->Bind(context, ProgrammableStage::VertexShaderStage, 2);
		}

		template <typename T, typename U>
		void Draw(std::shared_ptr<MeshBase<T, U>>& mesh, std::shared_ptr<WorldTransforms>& world, bool indexed = true)
		{
			auto context = m_deviceResources->GetD3DDeviceContext();

			world->Update(context);
			world->GetConstantBuffer()->Bind(context);

			mesh->BindVertexBuffer(context);
			mesh->BindIndexBuffer(context);

			if (indexed) mesh->DrawIndexed(context);
			else mesh->Draw(context);
		}

	private:
		std::shared_ptr<VertexShader<DirectX::VertexPositionNormalTexture>> _vertexshader;
		std::shared_ptr<PixelShader> _pixelshader;

		std::shared_ptr<MeshBase<DirectX::VertexPositionNormalTexture, unsigned short>> _model;

		std::shared_ptr<WorldTransforms> _world;
		std::shared_ptr<ViewTransform> _view;
		std::shared_ptr<ProjectionTransform> _projection;

		std::shared_ptr<Texture2D> _texture;
	};

}