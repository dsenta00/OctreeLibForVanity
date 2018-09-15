
#pragma once

//
//	Vertex Shader.h
//  Encapsulating a vertex shader object
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Shader Base.h"

#include "..\..\Core\Common\DirectXHelper.h"

#include "..\..\Utilities.h"

namespace vxe {

	// for a vertex type
	template <typename T>
	class VertexShader : public ShaderBase  {

	public:
		VertexShader() : _shader{ nullptr }, _layout{ nullptr } 
		{ 
		}

		concurrency::task<void> CreateAsync(_In_ ID3D11Device2* device, const std::wstring& filename) override
		{
			DebugPrint(std::string("\t VertexShader<") + typeid(T).name() + std::string(">::CreateAsync() ...\n"));

			return concurrency::create_task(DX::ReadDataAsync(filename)).then([this, device](const std::vector<byte> data)
			{
				DebugPrint(std::string("\t -- A lambda: Creating a VS and an IL \n"));

				vxe::ThrowIfFailed(device->CreateVertexShader(
					&data[0], 
					data.size(), 
					nullptr, 
					&_shader), __FILEW__, __LINE__);

				vxe::ThrowIfFailed(device->CreateInputLayout(
					T::InputElements, 
					T::InputElementCount, 
					&data[0], data.size(), 
					&_layout), __FILEW__, __LINE__);

				DebugPrint(std::string("\t -- A lambda: a VS and an IL created. \n"));
			});
		}

		virtual void Bind(_In_  ID3D11DeviceContext2* context, 
			ID3D11ClassInstance *const *instances = nullptr, 
			unsigned count = 0) override
		{
			//DebugPrint(std::string("\t VertexShader<") + typeid(T).name() + std::string(">::Bind() ...\n"));

			context->VSSetShader(_shader.Get(), instances, count);
			context->IASetInputLayout(_layout.Get());
		}

		void Reset()
		{
			DebugPrint(std::string("\t VertexShader<") + typeid(T).name() + std::string(">::Reset() ...\n"));

			_shader.Reset();
			_layout.Reset();
		}

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> _shader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> _layout;

		VertexShader(const VertexShader&) = delete;
		VertexShader(VertexShader&&) = delete;

		VertexShader& operator= (const VertexShader&) = delete;
		VertexShader& operator= (VertexShader&&) = delete;
	};

}