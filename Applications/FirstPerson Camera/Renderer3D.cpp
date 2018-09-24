
//
//	Renderer3D.cpp
//  Implementing a 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\..\Library\Engine\Models\Generated Shapes\Grid.h"

#include "Renderer3D.h"

using namespace vxe;
using namespace std;
using namespace concurrency;

using namespace DirectX;
using namespace Windows::Foundation;

void Renderer3D::CreateDeviceDependentResources()
{
	DebugPrint(string("\t Renderer3D::CreateDeviceDependentResources() ... \n"));

	auto device = m_deviceResources->GetD3DDevice();

	vector<task<void>> tasks;

	_vertexshader = make_shared<VertexShader<VertexPositionNormalTangentTexture>>();
	auto vstask = _vertexshader->CreateAsync(device, L"Vertex Shader.cso");
	tasks.push_back(vstask);

	_pixelshader = make_shared<PixelShader>();
	tasks.push_back(_pixelshader->CreateAsync(device, L"Pixel Shader.cso"));

	_model = make_shared<Grid<VertexPositionNormalTangentTexture, unsigned int>>(100.0f, 100.0f, 101, 101);
	tasks.push_back(_model->CreateAsync(device));

	when_all(tasks.begin(), tasks.end()).then([this]() {
		m_loadingComplete = true;
		DebugPrint(string("\t -- A lambda: Loading is complete! \n"));
	});

	_world = make_shared<WorldTransforms>(device);
}

// Initializes view parameters when the window size changes
void Renderer3D::CreateWindowSizeDependentResources()
{
	DebugPrint(string("\t Renderer3D::CreateWindowSizeDependentResources() ...\n"));

	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	_camera = std::make_shared<FirstPersonCamera>(device);

	//static const XMVECTORF32 eye = { 0.0f, 0.0f, 3.0f, 0.0f };
	static const XMVECTORF32 eye = { 0.0f, 10.0f, 15.0f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, 10.0f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	_camera->InitializeView(eye, at, up);
	_camera->UpdateView(context);
	_camera->UpdateEye(context);

	Size outputSize = m_deviceResources->GetOutputSize();
	DebugPrint(string("\t\t Width:") + to_string(outputSize.Width) + string("\n"));
	DebugPrint(string("\t\t Height:") + to_string(outputSize.Height) + string("\n"));

	float r = outputSize.Width / outputSize.Height;
	float fov = 70.0f * XM_PI / 180.0f;
	float n = 0.01f;
	float f = 1000.0f;

	if (r < 1.0f) { fov *= 2.0f; }

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();
	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	_camera->SetProjection(orientationMatrix, fov, r, n, f);
	_camera->UpdateProjection(context);
	_camera->BindProjection(context, ProgrammableStage::VertexShaderStage, 2);
}

// Renders one frame using the vertex and pixel shaders.
void Renderer3D::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete) { return; }

	auto context = m_deviceResources->GetD3DDeviceContext();

	//ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	//context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	_vertexshader->Bind(context);
	_pixelshader->Bind(context);

	BindCamera();

	Draw(_model, _world);

	m_deviceResources->SetRasterizerState();
}

void Renderer3D::ReleaseDeviceDependentResources()
{
	DebugPrint(string("\t Renderer3D::ReleaseDeviceDependentResources() ... \n"));

	m_loadingComplete = false;

	_vertexshader->Reset();
	_pixelshader->Reset();

	_model->Reset();

	_world->Reset();

	_camera->Reset();
}