
#pragma once

//
//	View Transform.h
//  Defining the view transform
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\..\Helpers.h"

#include "Data Transfer.h"

namespace vxe {

	enum class Handedness : byte {
		LeftHanded,
		RightHanded,
		Size
	};

	inline std::string ToString(Handedness h)
	{
		switch (h) {

		default: return "What a #%@$";

		case Handedness::LeftHanded: return "LeftHanded";
		case Handedness::RightHanded: return "RightHanded";
		}
	}

	class ViewTransform : public DataTransfer<DirectX::XMFLOAT4X4> {

	public:
		ViewTransform(_In_ ID3D11Device2* device, Handedness handedness = Handedness::LeftHanded)
			: DataTransfer{ device },
			_handedness{handedness}
		{
			DebugPrint(std::string("\t ViewTransform::Ctor ...\n"));
			DebugPrint(std::string("\t\t Handedness: ") + ToString(_handedness) + std::string("\n"));
		}

		void SetView(DirectX::FXMVECTOR eye, DirectX::FXMVECTOR at, DirectX::FXMVECTOR up)
		{
			DebugPrint(std::string("\t ViewTransform::SetView() ... \n"));

			DirectX::XMMATRIX view;

			if (_handedness == Handedness::LeftHanded)
				view = DirectX::XMMatrixLookAtLH(eye, at, up);
			else
				view = DirectX::XMMatrixLookAtRH(eye, at, up);

			DirectX::XMStoreFloat4x4(&_transfer, XMMatrixTranspose(view));

#if defined (_DEBUG)
			DirectX::XMFLOAT4X4 V;
			DirectX::XMStoreFloat4x4(&V, view);
			DebugPrint(std::string("\t\t View: " + ToString(&V) + "\n"));
#endif

		}

		DirectX::XMFLOAT4X4& GetView() { return _transfer; }

	private:
		Handedness _handedness;
	};

}