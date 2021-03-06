
//
//	Renderer3D.cpp
//  Implementing a 3D renderer
//
//  � 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Renderer3D.h"

#include "..\..\..\Library\Engine\Models\Basic Shapes\Pyramids.h"
#include "..\..\..\Library\Engine\Models\Basic Shapes\Cubes.h"
#include "..\..\..\Library\Engine\Models\Basic Shapes\Triangles.h"
#include "..\..\..\Library\Engine\Models\Explicit Surface.h"

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

	_vertexshader = make_shared<VertexShader<VertexPositionColor>>();
	auto vstask = _vertexshader->CreateAsync(device, L"Vertex Shader.cso");
	tasks.push_back(vstask);

    DebugPrint(std::string("Miljenko...\n"));
	_pixelshader = make_shared<PixelShader>();
	tasks.push_back(_pixelshader->CreateAsync(device, L"Pixel Shader.cso"));

    _models.push_back(make_shared<Pyramid<VertexPositionColor, unsigned short>>());
    _models.push_back(make_shared<Cube<VertexPositionColor, unsigned short>>());
    /*_models.push_back(make_shared<Triangle<VertexPositionColor, unsigned short>>());
    _models.push_back(make_shared<ExplicitSurface<VertexPositionColor, unsigned short>>(20.0f, 20.0f, 100, 100, [](float x, float z) {
        return 10 * expf(-(powf(x, 2.0f)) / 16.0f) * expf(-(powf(z, 2.0f)) / 16.0f);
    }));*/

    for (auto &_model : _models)
    {
        tasks.push_back(_model->CreateAsync(device));
    }

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

	_view = make_shared<ViewTransform>(device);

	//static const XMVECTORF32 eye = { 0.0f, 0.0f, 3.0f, 0.0f };
	static const XMVECTORF32 eye = { 0.0f, 10.0f, 15.0f, 0.0f };
	static const XMVECTORF32 at = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };

	_view->SetView(eye, at, up);
	_view->Update(context);

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

	SetCamera();

    for (auto &_model : _models) 
    {
        Draw(_model, _world);
    }

	m_deviceResources->SetRasterizerState();
}

void Renderer3D::ReleaseDeviceDependentResources()
{
	DebugPrint(string("\t Renderer3D::ReleaseDeviceDependentResources() ... \n"));

	m_loadingComplete = false;

	_vertexshader->Reset();
	_pixelshader->Reset();

    for (auto &_model : _models) 
    {
        _model->Reset();
    }

	_world->Reset();
	_view->Reset();
	_projection->Reset();
}