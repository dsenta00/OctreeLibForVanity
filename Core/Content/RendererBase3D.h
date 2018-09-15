
#pragma once

//
//	RendererBase3D.h
//  Defining a base 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

#include "..\Scene\Input\Input Controller.h"

namespace vxe
{
	// This renderer instantiates a basic rendering pipeline.
	class RendererBase3D {

	public:
		RendererBase3D(InputController^ inputcontroller = nullptr) :
			_inputcontroller(inputcontroller),
			m_loadingComplete(false),
			m_degreesPerSecond(45),
			m_tracking(false)
		{
			DebugPrint(std::string("\t RendererBase3D::Ctor... \n"));
		}

		~RendererBase3D() {};

		void Initialize(const std::shared_ptr<DX::DeviceResources>& deviceResources);

		virtual void CreateDeviceDependentResources() { };
		virtual void CreateWindowSizeDependentResources() { };
		virtual void ReleaseDeviceDependentResources() { };
		virtual void Update(DX::StepTimer const&);
		virtual void Render() = 0;
		virtual void TrackingUpdate(float);

		void SetWindow(Windows::UI::Core::CoreWindow^ window)
		{
			if (_inputcontroller != nullptr) _inputcontroller->Initialize(window);
		}

		virtual void StartTracking() { m_tracking = true; };
		virtual void StopTracking() { m_tracking = true; };
		virtual bool IsTracking() { return m_tracking; }

		virtual void Rotate(float radians) { };

	protected:
		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		InputController^ _inputcontroller;

		// Variables used with the rendering loop.
		bool	m_loadingComplete;
		float	m_degreesPerSecond;
		bool	m_tracking;
	};
}