
#pragma once

//
//	Resource Factory.h
//  A singleton factory for creating various resources and views
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\Utilities.h"

namespace vxe {

    class ResourceFactory {

    private:
        static std::unique_ptr<ResourceFactory> _instance;
        static std::once_flag _flag;

        ResourceFactory() {};

    public:
        // NOTE: The unique_ptr will invoke the destructor
        virtual ~ResourceFactory() { }

        static ResourceFactory &Instance()
        {
            std::call_once(_flag, [] { _instance.reset(new ResourceFactory); });

            return *_instance.get();
        }

        // Writen by the pipeline, read for blending
        void CreateRenderTargetView(_In_ ID3D11Device2* device, _In_ IDXGISwapChain1* swapchain, CD3D11_RENDER_TARGET_VIEW_DESC* desc, ID3D11RenderTargetView** pp)
        {
            DebugPrint(std::string("\t\t ResourceFactory::CreateRenderTargetView() ...\n"));

            Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
            ThrowIfFailed(swapchain->GetBuffer(0,
                __uuidof(ID3D11Texture2D),
                &backbuffer), __FILEW__, __LINE__);

            ThrowIfFailed(device->CreateRenderTargetView(backbuffer.Get(), desc, pp), __FILEW__, __LINE__);
        }

        void CreateRenderTargetView(_In_ ID3D11Device2* device, _In_ ID3D11Texture2D* texture, ID3D11RenderTargetView** pp)
        {
            DebugPrint(std::string("\t\t ResourceFactory::CreateRenderTargetView() ...\n"));

            ThrowIfFailed(device->CreateRenderTargetView(texture, nullptr, pp), __FILEW__, __LINE__);
        }

        //	Depth stencil tests (RW)
        void CreateDepthStencilView(_In_ ID3D11Device2* device, CD3D11_TEXTURE2D_DESC* texturedesc, ID3D11DepthStencilView** pp)
        {
            DebugPrint(std::string("\t\t ResourceFactory::CreateDepthStencilView() ...\n"));

            Microsoft::WRL::ComPtr<ID3D11Texture2D> depthstencil;
            ThrowIfFailed(device->CreateTexture2D(texturedesc, nullptr, &depthstencil), __FILEW__, __LINE__);

            auto desc = CD3D11_DEPTH_STENCIL_VIEW_DESC(D3D11_DSV_DIMENSION_TEXTURE2D);
            ThrowIfFailed(device->CreateDepthStencilView(depthstencil.Get(), &desc, pp), __FILEW__, __LINE__);
        }

        void CreateTargetBitmap(_In_ IDXGISwapChain1* swapchain, _In_ ID2D1DeviceContext1* context, D2D1_BITMAP_PROPERTIES1* properties, ID2D1Bitmap1** pp)
        {
            DebugPrint(std::string("\t\t ResourceFactory::CreateTargetBitmap() ...\n"));

            Microsoft::WRL::ComPtr<IDXGISurface2> surface;

            ThrowIfFailed(swapchain->GetBuffer(0, IID_PPV_ARGS(&surface)), __FILEW__, __LINE__);

            ThrowIfFailed(context->CreateBitmapFromDxgiSurface(surface.Get(), properties, pp), __FILEW__, __LINE__);
        }

        //	Can be attached to all shaders. Provides a read-access in a shader
        void CreateShaderResourceView(_In_ ID3D11Device2*, _In_ ID3D11Resource*, CD3D11_SHADER_RESOURCE_VIEW_DESC*, ID3D11ShaderResourceView**);

        //	Can be attached to CS and PS. Provides a read-write in the same shader
        void CreateUnorderedAccessView(_In_ ID3D11Device2*, _In_ ID3D11Resource*, CD3D11_UNORDERED_ACCESS_VIEW_DESC*, ID3D11UnorderedAccessView**);

    private:
        ResourceFactory(const ResourceFactory&) = delete;
        ResourceFactory(ResourceFactory&&) = delete;

        ResourceFactory& operator= (const ResourceFactory&) = delete;
        ResourceFactory& operator= (ResourceFactory&&) = delete;
    };

}
