
#pragma once

//
//	Texture Base.h
//  Encaspulates views and a sampler state
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Pipeline Stages\State Factory.h"
#include "..\Resource Factory.h"

#include "..\..\Pipeline Stages\Shaders\Shader Base.h"

namespace vxe {

	class TextureBase  {

	public:
		TextureBase(ID3D11Device2* device)
			: _device{ device },
			_samplerstate{ nullptr },
			_srv{ nullptr },
			_uav{ nullptr } { }

		bool CreateSamplerState(CD3D11_SAMPLER_DESC& desc)
		{
			DebugPrint(std::string("\t TextureBase::CreateSamplerState() ...\n"));

			StateFactory::Instance().CreateSamplerState(
				_device.Get(),
				&desc,
				&_samplerstate);
		}

		void CreateSamplerState()
		{
			DebugPrint(std::string("\t TextureBase::CreateSamplerState() ...\n"));

			CD3D11_SAMPLER_DESC desc(CD3D11_DEFAULT{});

			desc.Filter = D3D11_FILTER_ANISOTROPIC;
			//desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			desc.MaxAnisotropy = 16;
			desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			desc.MinLOD = 0;
			desc.MaxLOD = D3D11_FLOAT32_MAX;

			// Border address mode is not used, so this parameter is ignored.
			for (int i = 0; i < 4; i++) desc.BorderColor[i] = 0.0f;

			StateFactory::Instance().CreateSamplerState(
				_device.Get(),
				&desc,
				&_samplerstate);
		}

		void BindSamplerState(_In_ ID3D11DeviceContext2* context, unsigned slot = 0, unsigned count = 1)
		{
			DebugPrint(std::string("\t TextureBase::BindSamplerState() ...\n"));

			if (_uav == nullptr) {
				DebugPrint(std::string("\t\t _samplerstate is nullptr. \n"));

				return;
			}

			context->PSSetSamplers(slot, count, _samplerstate.GetAddressOf());
		}

		virtual bool CreateShaderResourceView() = 0;

		virtual bool CreateUnorderedAccessView() = 0;

		void BindShaderResourceView(_In_ ID3D11DeviceContext2* context,
			ProgrammableStage shader = ProgrammableStage::PixelShaderStage,
			unsigned slot = 0,
			unsigned count = 1)
		{
			DebugPrint(std::string("\t TextureBase::BindShaderResourceView() ...\n"));

			if (_srv == nullptr) {
				DebugPrint(std::string("\t\t _srv is nullptr. \n"));

				return;
			}

			if (shader == ProgrammableStage::VertexShaderStage) {
				context->VSSetShaderResources(slot, count, _srv.GetAddressOf());
			}
			else if (shader == ProgrammableStage::PixelShaderStage) {
				context->PSSetShaderResources(slot, count, _srv.GetAddressOf());
			}
			else if (shader == ProgrammableStage::ComputeShaderStage) {
				context->CSSetShaderResources(slot, count, _srv.GetAddressOf());
			}
			else
				return;
		}

		void UnbindShaderResourceView(_In_ ID3D11DeviceContext2* context,
			ProgrammableStage shader = ProgrammableStage::PixelShaderStage,
			unsigned slot = 0,
			unsigned count = 1)
		{
			DebugPrint(std::string("\t TextureBase::UnbindShaderResourceView() ...\n"));

			ID3D11ShaderResourceView* srv = nullptr;

			if (shader == ProgrammableStage::VertexShaderStage) {
				context->VSSetShaderResources(slot, count, &srv);
			}
			else if (shader == ProgrammableStage::PixelShaderStage) {
				context->PSSetShaderResources(slot, count, &srv);
			}
			else if (shader == ProgrammableStage::ComputeShaderStage) {
				context->CSSetShaderResources(slot, count, &srv);
			}
			else
				return;
		}

		void BindUnorderedAccessView(_In_ ID3D11DeviceContext2* context,
			ProgrammableStage = ProgrammableStage::ComputeShaderStage,
			unsigned slot = 0,
			unsigned count = 1)
		{
			DebugPrint(std::string("\t TextureBase::BindUnorderedAccessView() ...\n"));

			if (_uav == nullptr) {
				DebugPrint(std::string("\t\t _srv is nullptr. \n"));

				return;
			}

			context->CSSetUnorderedAccessViews(slot, count, _uav.GetAddressOf(), nullptr);
		}

		void UnbindUnorderedAccessView(_In_ ID3D11DeviceContext2* context,
			unsigned slot = 0,
			unsigned count = 1)
		{
			DebugPrint(std::string("\t TextureBase::UnbindUnorderedAccessView() ...\n"));

			// TO DO: assert _uav
			ID3D11UnorderedAccessView* uav = nullptr;

			context->CSSetUnorderedAccessViews(slot, count, &uav, nullptr);
		}

		void Reset()
		{
			DebugPrint(std::string("\t TextureBase::Reset() ...\n"));

			if (_samplerstate != nullptr) _samplerstate.Reset();

			if (_srv != nullptr) _srv.Reset();
			if (_uav != nullptr)_uav.Reset();
		}

	protected:
		Microsoft::WRL::ComPtr<ID3D11Device2> _device;

		Microsoft::WRL::ComPtr<ID3D11SamplerState> _samplerstate;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> _uav;
		// Add additionals views

	private:
		TextureBase(const TextureBase&) = delete;
		TextureBase(TextureBase&&) = delete;

		TextureBase& operator= (const TextureBase&) = delete;
		TextureBase& operator= (TextureBase&&) = delete;
	};
}