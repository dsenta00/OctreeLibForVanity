
#pragma once

//
//	SwapChainDescription.h
//  Description of the swap chain object
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

namespace vxe {

	class SwapChainDescription {

	public:
		DXGI_SWAP_CHAIN_DESC1 _description;

	public:
		SwapChainDescription(float width = 0, float height = 0)
		{
			_description.Width = lround(width);
			_description.Height = lround(height);
			_description.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			_description.Stereo = false;
			_description.SampleDesc.Count = 1;
			_description.SampleDesc.Quality = 0;
			_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			_description.BufferCount = 2;
			_description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			_description.Flags = 0;
			_description.Scaling = DXGI_SCALING_NONE;
			_description.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
		}

		DXGI_SWAP_CHAIN_DESC1* Get() { return &_description; }

		void SetWidth(unsigned int width)  { _description.Width = width; }
		void SetHeight(unsigned int height) { _description.Height = height; }
		void SetFormat(DXGI_FORMAT format) { _description.Format = format; }
		void SetStereo(bool stereo) { _description.Stereo = stereo; }
		void SetSampleDescCount(unsigned int count) { _description.SampleDesc.Count = count; }
		void SetSampleDescQuality(unsigned int quality) { _description.SampleDesc.Quality = quality; }
		void SetBufferUsage(DXGI_USAGE usage) { _description.BufferUsage = usage; }
		void SetBufferCount(unsigned count) { _description.BufferCount = count; }
		void SetSwapEffect(DXGI_SWAP_EFFECT effect) { _description.SwapEffect = effect; }
		void SetFlags(unsigned flags) { _description.Flags = flags; }
		void SetScaling(DXGI_SCALING scaling) { _description.Scaling = scaling; }
		void SetAlphaMode(DXGI_ALPHA_MODE mode) { _description.AlphaMode = mode; }
	};

}