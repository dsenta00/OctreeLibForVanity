
#pragma once

//
//	Camera Base.h
//	Encapsulates basic camera elements: position, view and projection
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\Transforms\Position.h"
#include "..\Transforms\View Transform.h"
#include "..\Transforms\Projection Transform.h"

namespace vxe {

	class CameraBase {

	public:
		CameraBase(_In_ ID3D11Device2* device)
			: _eye{ device }, 
			_view{ device }, 
			_projection{ device } 
		{ }

		void InitializeView(DirectX::FXMVECTOR eye, DirectX::FXMVECTOR lookat, DirectX::FXMVECTOR up)
		{
			DebugPrint(std::string("\t CameraBase::InitializeView() \n"));

			_eye.SetPosition(eye);
			DirectX::XMStoreFloat3(&_lookat, lookat);
			DirectX::XMStoreFloat3(&_up, up);

			_view.SetView(eye, lookat, up);
		}

		void SetView()
		{
			auto eye = _eye.GetPosition();
			auto lookat = DirectX::XMLoadFloat3(&_lookat);
			auto up = DirectX::XMLoadFloat3(&_up);

			_view.SetView(eye, lookat, up);
		}

		DirectX::XMVECTOR GetEye() { return _eye.GetPosition(); }

		inline DirectX::XMVECTOR GetLookAt() 
		{
			auto lookat = DirectX::XMLoadFloat3(&_lookat);

			return lookat;
		}

		inline DirectX::XMVECTOR GetUp()
		{
			auto up = DirectX::XMLoadFloat3(&_up);

			return up;
		}

		void SetProjection(DirectX::CXMMATRIX orientation, float a, float b, float zn, float zf)
		{
			_projection.SetProjection(orientation, a, b, zn, zf);
		}

		void UpdateEye(_In_ ID3D11DeviceContext2* context) { _eye.Update(context); }
		void UpdateView(_In_ ID3D11DeviceContext2* context) { _view.Update(context); }
		void UpdateProjection(_In_ ID3D11DeviceContext2* context) { _projection.Update(context); }

		void BindEye(_In_ ID3D11DeviceContext2* context,
			ProgrammableStage shader = ProgrammableStage::PixelShaderStage,
			unsigned slot = 0,
			unsigned count = 1)
		{
			_eye.GetConstantBuffer()->Bind(context, shader, slot, count);
		}

		void BindView(_In_ ID3D11DeviceContext2* context,
			ProgrammableStage shader = ProgrammableStage::VertexShaderStage,
			unsigned slot = 0,
			unsigned count = 1)
		{
			_view.GetConstantBuffer()->Bind(context, shader, slot, count);
		}

		void BindProjection(_In_ ID3D11DeviceContext2* context,
			ProgrammableStage shader = ProgrammableStage::VertexShaderStage,
			unsigned slot = 0,
			unsigned count = 1)
		{
			_projection.GetConstantBuffer()->Bind(context, shader, slot, count);
		}

		void Reset()
		{
			DebugPrint(std::string("\t\t CameraBase::Reset() ...\n"));

			_eye.Reset();
			_view.Reset();
			_projection.Reset();
		}
	
	protected:
		Position _eye;
		DirectX::XMFLOAT3 _lookat;
		DirectX::XMFLOAT3 _up;

		ViewTransform _view;
		ProjectionTransform _projection;
	};
}