
#pragma once

//
//	Projection Transform.h
//  Defining the projection transform
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\..\Helpers.h"

#include "Data Transfer.h"
#include "View Transform.h"

namespace vxe {

	enum class Projection : byte {
		Perspective,
		Orthographic,
		Size
	};

	inline std::string ToString(Projection p)
	{
		switch (p) {

		default: return "What a #%@$";

		case Projection::Perspective: return "Perspective";
		case Projection::Orthographic: return "Orthographic";
		}
	}

	class ProjectionTransform : public DataTransfer<DirectX::XMFLOAT4X4> {

	public:
		ProjectionTransform(_In_ ID3D11Device2* device, Handedness h = Handedness::LeftHanded, Projection t = Projection::Perspective)
			: DataTransfer{device},
			_handedness{ h },
			_projectiontype{ t }
		{
			DebugPrint(std::string("\t ProjectionTransform::Ctor ...\n"));
			DebugPrint(std::string("\t\t Handedness: ") + ToString(_handedness) + std::string("\n"));
			DebugPrint(std::string("\t\t Projection: ") + ToString(_projectiontype) + std::string("\n"));
		}

		void SetProjection(DirectX::CXMMATRIX orientation, float a, float b, float zn, float zf)
		{
			DebugPrint(std::string("\t ProjectionTransform::SetProjection() ... \n"));

			DirectX::XMMATRIX projection;

			if (_handedness == Handedness::LeftHanded) {

				if (_projectiontype == Projection::Perspective)
					projection = DirectX::XMMatrixPerspectiveFovLH(a, b, zn, zf);
				else
					projection = DirectX::XMMatrixOrthographicLH(a, b, zn, zf);
			} else {

				if (_projectiontype == Projection::Perspective)
					projection = DirectX::XMMatrixPerspectiveFovRH(a, b, zn, zf);
				else
					projection = DirectX::XMMatrixOrthographicRH(a, b, zn, zf);
			}

#if defined (_DEBUG)
			DirectX::XMFLOAT4X4 P;
			DirectX::XMStoreFloat4x4(&P, projection);
			DebugPrint(std::string("\t\t Projection: " + ToString(&P) + "\n"));
#endif

			DirectX::XMStoreFloat4x4(&_transfer, DirectX::XMMatrixTranspose(projection * orientation));
		}

		DirectX::XMFLOAT4X4& GetProjection() { return _transfer; }

	private:
		Handedness _handedness;
		Projection _projectiontype;	// projection type
	};

}