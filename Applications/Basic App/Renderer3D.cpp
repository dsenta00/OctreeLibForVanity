
//
//	Renderer3D.cpp
//  Implementing a 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

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

	when_all(tasks.begin(), tasks.end()).then([this]() {
		m_loadingComplete = true;
		DebugPrint(string("\t -- A lambda: Loading is complete! \n"));
	});
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
}

// Renders one frame using the vertex and pixel shaders.
void Renderer3D::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete) { return; }

	auto context = m_deviceResources->GetD3DDeviceContext();

	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	m_deviceResources->SetRasterizerState();
}

void Renderer3D::ReleaseDeviceDependentResources()
{
	DebugPrint(string("\t Renderer3D::ReleaseDeviceDependentResources() ... \n"));

	m_loadingComplete = false;
}