
//
//	StateFactory.cpp
//  A singleton factory for creating various states
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "State Factory.h"

using namespace std;

std::unique_ptr<vxe::StateFactory> vxe::StateFactory::_instance = nullptr;
std::once_flag vxe::StateFactory::_flag;

void vxe::StateFactory::CreateRasterizerState(_In_ ID3D11Device2* device, D3D11_FILL_MODE fill, D3D11_CULL_MODE cull, bool fccw, ID3D11RasterizerState1** pp)
{
	CD3D11_RASTERIZER_DESC1 desc(CD3D11_DEFAULT{});
	desc.FillMode = fill;
	desc.CullMode = cull;
	desc.FrontCounterClockwise = fccw;

	device->CreateRasterizerState1(&desc, pp);
}

void vxe::StateFactory::CreatBlendState(_In_ ID3D11Device2* device, ID3D11BlendState1** pp)
{
	CD3D11_BLEND_DESC1 desc(CD3D11_DEFAULT{});

	//ZeroMemory(&desc, sizeof(desc));

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	desc.RenderTarget[0].BlendEnable = TRUE;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;

	ThrowIfFailed(device->CreateBlendState1(&desc, pp), __FILEW__, __LINE__);
}