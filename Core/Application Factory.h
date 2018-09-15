
#pragma once

//
//	Application Factory.h
//  Defining the aplication factory
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "App.h"
#include "Content\RendererBase3D.h"

namespace vxe {

	ref class ApplicationFactory sealed : Windows::ApplicationModel::Core::IFrameworkViewSource{

	internal:
		App^ _application;
		std::shared_ptr<RendererBase3D> _renderer3D;

		//The public surface area of a WinRT type can only contain WinRT compatible types
		ApplicationFactory(const std::shared_ptr<RendererBase3D>& renderer3D)
			: _renderer3D(renderer3D)
		{
			DebugPrint(std::string("ApplicationFactory::Ctor ...\n"));
		}

	public:
		virtual ~ApplicationFactory()
		{
			DebugPrint(std::string("ApplicationFactory::Dtor ...\n"));
		}

		virtual Windows::ApplicationModel::Core::IFrameworkView ^CreateView()
		{
			DebugPrint(std::string("ApplicationFactory::CreateView() ...\n"));

			_application = ref new App(_renderer3D);

			return _application;
		}
	};
}