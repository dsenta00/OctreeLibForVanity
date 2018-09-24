
#pragma once

//
//	Renderer3D.h
//  Defining a 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\..\Library\Engine\Third Party\DirectX Tool Kit\VertexTypes.h"

#include "..\..\..\Library\Engine\Pipeline Stages\Shaders\Vertex Shader.h"
#include "..\..\..\Library\Engine\Pipeline Stages\Shaders\Pixel Shader.h"

#include "..\..\..\Library\Engine\Models\Mesh Base.h"
#include "..\..\..\Library\Engine\Scene\Transforms\World Transforms.h"

#include "..\..\..\Library\Engine\Scene\Cameras\FirstPerson Camera.h"
#include "..\..\..\Library\Engine\Scene\Input\Input Controller.h"

namespace vxe
{
	class Renderer3D : public RendererBase3D {

	public:
		Renderer3D::Renderer3D(InputController^ inputcontroller = nullptr) : 
			RendererBase3D(inputcontroller)
		{
			DebugPrint(std::string("\t Renderer3D::Ctor... \n"));
		}

		virtual void CreateDeviceDependentResources() override;
		virtual void CreateWindowSizeDependentResources() override;
		virtual void ReleaseDeviceDependentResources() override;

		virtual void Update(DX::StepTimer const& timer) override
		{
			RendererBase3D::Update(timer);

			_camera->Update(_inputcontroller, timer);
		}
		
		virtual void Render() override;

	private:
		void BindCamera()
		{
			auto context = m_deviceResources->GetD3DDeviceContext();

			_camera->UpdateEye(context);
			_camera->BindEye(context, ProgrammableStage::PixelShaderStage, 1);

			_camera->UpdateView(context);
			_camera->BindView(context, ProgrammableStage::VertexShaderStage, 1);
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
		std::shared_ptr<VertexShader<DirectX::VertexPositionNormalTangentTexture>> _vertexshader;
		std::shared_ptr<PixelShader> _pixelshader;

		std::shared_ptr<MeshBase<DirectX::VertexPositionNormalTangentTexture, unsigned int>> _model;
		std::shared_ptr<WorldTransforms> _world;

		std::shared_ptr<FirstPersonCamera> _camera;
	};

}