
#pragma once

//
//	StateFactory.h
//  A singleton factory for creating various states
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\Utilities.h"

namespace vxe {

	class StateFactory {

	private:
		StateFactory() { };

		static std::unique_ptr<StateFactory> _instance;
		static std::once_flag _flag;

	public:
		virtual ~StateFactory() { }

		inline static StateFactory &Instance()
		{
			std::call_once(_flag, [] { _instance.reset(new StateFactory); });

			return *_instance.get();
		}

		void CreateRasterizerState(_In_ ID3D11Device2* device, CD3D11_RASTERIZER_DESC* desc, ID3D11RasterizerState** pp)
		{
			ThrowIfFailed(device->CreateRasterizerState(desc, pp), __FILEW__, __LINE__);
		}

		void CreateRasterizerState(_In_ ID3D11Device2* device, D3D11_FILL_MODE fill, D3D11_CULL_MODE cull, bool fccw, ID3D11RasterizerState1** pp);

		void CreateRasterizerState(_In_ ID3D11Device2* device, CD3D11_RASTERIZER_DESC1* desc, ID3D11RasterizerState1** pp)
		{
			ThrowIfFailed(device->CreateRasterizerState1(desc, pp), __FILEW__, __LINE__);
		}

		void CreateSamplerState(_In_ ID3D11Device2* device, CD3D11_SAMPLER_DESC* desc, ID3D11SamplerState** pp)
		{
			ThrowIfFailed(device->CreateSamplerState(desc, pp), __FILEW__, __LINE__);
		}

		void CreatBlendState(_In_ ID3D11Device2* device, ID3D11BlendState1** pp);

		void CreatBlendState(_In_ ID3D11Device2* device, CD3D11_BLEND_DESC1* desc, ID3D11BlendState1** pp)
		{
			ThrowIfFailed(device->CreateBlendState1(desc, pp), __FILEW__, __LINE__);
		}

	private:
		StateFactory(const StateFactory&) = delete;
		StateFactory(StateFactory&&) = delete;

		StateFactory& operator= (const StateFactory&) = delete;
		StateFactory& operator= (StateFactory&&) = delete;
	};
}