
#pragma once

//
//	PixelShader.h
//  Encapsulating a pixel shader object
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h" 

#include "Shader Base.h"
#include "..\..\Core\Common\DirectXHelper.h"

namespace vxe {

	class PixelShader : public ShaderBase  {

	public:
		PixelShader() : _shader{ nullptr } { }

		concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::wstring& filename) override
		{
			DebugPrint(std::string("\t PixelShader::CreateAsync() ...\n"));

			return concurrency::create_task(DX::ReadDataAsync(filename)).then([this, device](const std::vector<byte> data) {

				DebugPrint(std::string("\t -- A lambda: Creating a PS ...\n"));

				vxe::ThrowIfFailed(device->CreatePixelShader(
					&data[0], 
					data.size(), 
					nullptr, 
					&_shader), __FILEW__, __LINE__);

				DebugPrint(std::string("\t -- A lambda: a PS created.\n"));
			});
		}

		virtual void Bind(_In_ ID3D11DeviceContext2* context, ID3D11ClassInstance *const *instances = nullptr, unsigned count = 0) override
		{
			//DebugPrint(std::string("\t PixelShader::Bind() ...\n"));

			context->PSSetShader(_shader.Get(), instances, count);
		}

		void Reset()
		{
			DebugPrint(std::string("\t PixelShader::Reset() ...\n"));
			_shader.Reset();
		}

	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _shader;

		PixelShader(const PixelShader&) = delete;
		PixelShader(PixelShader&&) = delete;

		PixelShader& operator= (const PixelShader&) = delete;
		PixelShader& operator= (PixelShader&&) = delete;
	};

}