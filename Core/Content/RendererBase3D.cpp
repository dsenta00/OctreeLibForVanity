//
//	RendererBase3D.cpp
//  Defining a base 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "RendererBase3D.h"

using namespace vxe;
using namespace std;
using namespace DirectX;

void RendererBase3D::Initialize(const shared_ptr<DX::DeviceResources>& deviceResources)
{
	DebugPrint(std::string("\t RendererBase3D::Initialize()... \n"));

	m_deviceResources = deviceResources;

	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Called once per frame, rotates the model 
void RendererBase3D::Update(DX::StepTimer const& timer)
{
	if (!m_tracking)
	{
		// Convert degrees to radians, then convert seconds to rotation angle
		float radiansPerSecond = XMConvertToRadians(m_degreesPerSecond);
		double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(totalRotation, XM_2PI));

		Rotate(radians);
	}
}

// When tracking, the 3D model can be rotated around its Y axis by tracking pointer position relative to the output screen width.
void RendererBase3D::TrackingUpdate(float positionX)
{
	if (m_tracking)
	{
		float radians = XM_2PI * 2.0f * positionX / m_deviceResources->GetOutputSize().Width;
		Rotate(radians);
	}
}