
//
//	Renderer3D.cpp
//  Implementing a 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Renderer3D.h"

#include "..\..\..\Library\Engine\Models\Basic Shapes\Cubes.h"

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

	_vertexshader = make_shared<VertexShader<VertexPositionNormal>>();
	auto vstask = _vertexshader->CreateAsync(device, L"Lighting VertexShader.cso");
	tasks.push_back(vstask);

	_pixelshader = make_shared<PixelShader>();
	tasks.push_back(_pixelshader->CreateAsync(device, L"Lighting PixelShader.cso"));

	_model = make_shared<Cube<VertexPositionNormal, unsigned short>>();
	tasks.push_back(_model->CreateAsync(device));

	when_all(tasks.begin(), tasks.end()).then([this]() {
		m_loadingComplete = true;
		DebugPrint(string("\t -- A lambda: Loading is complete! \n"));
	});

	_world = make_shared<WorldTransforms>(device);

	SetLighting();
}

void Renderer3D::SetLighting()
{
	DebugPrint(string("\t Renderer3D::SetLighting() ...\n"));

	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	XMFLOAT4 ambient = XMFLOAT4(0.9f, 0.1f, 0.5f, 1.0f);
	XMFLOAT4 diffuse = XMFLOAT4(0.3f, 0.5f, 0.7f, 1.0f);
	XMFLOAT4 specular = XMFLOAT4(0.7f, 0.3f, 0.1f, 16.0f);
	XMFLOAT4 reflection = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	_material = make_shared<Material>(device);
	_material->SetComponents(ambient, diffuse, specular, reflection);

	_material->Update(context);
	_material->GetConstantBuffer()->Bind(context, ProgrammableStage::PixelShaderStage);

	ambient = XMFLOAT4(0.6f, 0.1f, 0.1f, 1.0f);
	diffuse = XMFLOAT4(0.6f, 0.5f, 0.3f, 1.0f);
	specular = XMFLOAT4(0.4f, 0.5f, 0.1f, 1.0f);
	XMFLOAT3 direction = XMFLOAT3(-0.5f, 0.5f, 0.3f);

	_directional = make_shared<DirectionalLight>(device);
	_directional->SetComponents(ambient, diffuse, specular, direction);
	_directional->Update(context);
	_directional->GetConstantBuffer()->Bind(context, ProgrammableStage::PixelShaderStage, 2);
}

// Initializes view parameters when the window size changes
void Renderer3D::CreateWindowSizeDependentResources()
{
	DebugPrint(string("\t Renderer3D::CreateWindowSizeDependentResources() ...\n"));

	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	Size outputSize = m_deviceResources->GetOutputSize();
	DebugPrint(string("\t\t Width:") + to_string(outputSize.Width) + string("\n"));
	DebugPrint(string("\t\t Height:") + to_string(outputSize.Height) + string("\n"));

	_view = make_shared<ViewTransform>(device);

	static const XMVECTORF32 eye = { 0.0f, 0.0f, -3.0f, 0.0f };
	//static const XMVECTORF32 eye = { 0.0f, 10.0f, 15.0f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	_view->SetView(eye, at, up);
	_view->Update(context);

	_eye = make_shared<Position>(device);
	_eye->SetPosition(eye);
	_eye->Update(context);

	float r = outputSize.Width / outputSize.Height;
	float fov = 70.0f * XM_PI / 180.0f;
	float n = 0.01f;
	float f = 1000.0f;

	if (r < 1.0f) { fov *= 2.0f; }

	XMFLOAT4X4 orientation = m_deviceResources->GetOrientationTransform3D();
	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	_projection = make_shared<ProjectionTransform>(device);
	_projection->SetProjection(orientationMatrix, fov, r, n, f);
	_projection->Update(context);
}

// Renders one frame using the vertex and pixel shaders.
void Renderer3D::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete) { return; }

	auto context = m_deviceResources->GetD3DDeviceContext();

	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	_vertexshader->Bind(context);
	_pixelshader->Bind(context);

	Draw(_model, _world);

	SetCamera();

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
	_view->Reset();
	_eye->Reset();
	_projection->Reset();

	_material->Reset();
	_directional->Reset();
}