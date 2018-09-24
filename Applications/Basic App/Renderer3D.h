
#pragma once

//
//	Renderer3D.h
//  Defining a 3D renderer
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

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
	};

}