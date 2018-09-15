
#pragma once

//
//	Texture2D.h
//  Encaspulating a 2D texture 
//
//  © 2015 Genuine3D DirectX 11.2 Engine (GXE). All rights reserved.
//

#include "pch.h"

#include "Texture Base.h"

#include "..\..\Third Party\DirectX Tool Kit\DDS\DDSTextureLoader.h"
#include "..\..\Third Party\DirectX Tool Kit\WIC\WICTextureLoader.h"

namespace vxe {

	class Texture2D : public TextureBase {

	protected:
		CD3D11_TEXTURE2D_DESC _description;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _texture;

	public:
		explicit Texture2D(ID3D11Device2* device,
			DXGI_FORMAT format,
			unsigned int width = 0,
			unsigned int height = 0,
			unsigned int arraysize = 1,
			unsigned int miplevels = 1,
			unsigned int bindflags = D3D11_BIND_SHADER_RESOURCE,
			D3D11_USAGE usage = D3D11_USAGE_DEFAULT,
			unsigned int cpuflags = 0,
			unsigned int samplecount = 1,
			unsigned int samplequality = 0,
			unsigned int miscflags = 0) :

			_texture{ nullptr },
			TextureBase(device),
			_description(format, width, height, arraysize, miplevels, bindflags, usage, cpuflags, samplecount, samplequality, miscflags)
		{
			DebugPrint(std::string("\t Texture2D::Ctor ...\n"));
		}

		concurrency::task<void> CreateAsync(const std::wstring&, unsigned = 1024, unsigned = 0);

		// The wrappers for DirectX Tool Kit WIC functions
		void CreateWIC(_In_opt_ ID3D11DeviceContext*, _In_z_ const std::wstring&, _In_ size_t = 0);

		// The wrappers for DirectX Tool Kit DDS functions
		void CreateDDS(ID3D11DeviceContext*, _In_z_ const std::wstring&, _In_ size_t = 0, _Out_opt_ DirectX::DDS_ALPHA_MODE* = nullptr);
		concurrency::task<void> CreateDDSAsync(_In_opt_ ID3D11DeviceContext*, _In_z_ const std::wstring&, _In_ size_t = 0, _Out_opt_ DirectX::DDS_ALPHA_MODE* = nullptr);

		virtual bool CreateShaderResourceView() override
		{
			DebugPrint(std::string("\t Texture2D::CreateShaderResourceView() \n"));
			CD3D11_SHADER_RESOURCE_VIEW_DESC desc(D3D11_SRV_DIMENSION_TEXTURE2D, _description.Format, 0, _description.MipLevels);

			ResourceFactory::Instance().CreateShaderResourceView(_device.Get(), _texture.Get(), &desc, &_srv);

			return true;
		}

		virtual bool CreateUnorderedAccessView() override
		{
			DebugPrint(std::string("\t Texture2D::CreateUnorderedAccessView() \n"));

			int count = _description.Width * _description.Height;
			CD3D11_UNORDERED_ACCESS_VIEW_DESC desc(D3D11_UAV_DIMENSION_TEXTURE2D, _description.Format, 0, count);
			ResourceFactory::Instance().CreateUnorderedAccessView(_device.Get(), _texture.Get(), &desc, &_uav);

			return true;
		}

		ID3D11Texture2D* GetTexture() const { return _texture.Get(); }

		int GetWidth() { return _description.Width; }

		int GetHeight() { return _description.Height; }

		void Reset()
		{
			DebugPrint(std::string("\t Texture2D::Reset() ...\n"));

			TextureBase::Reset();

			_texture.Reset();
		}

	public:
		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;

		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (Texture2D&&) = delete;
	};

}