
#pragma once

//
//	Helpers.h
//  Helpers for mathematical operations and text
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

namespace vxe {

	inline DirectX::XMMATRIX GetInverseMatrix(DirectX::CXMMATRIX M)
	{
		DirectX::XMMATRIX A = M;

		// removing the translation
		//A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
		return DirectX::XMMatrixInverse(&det, A);
	}

#if defined (_DEBUG)

	inline std::string ToString(DirectX::XMFLOAT3 *vector)
	{
		std::stringstream ss;

		ss << std::setprecision(7);

		ss << "[ " << vector->x << " " << vector->y << " " << vector->z << " ]";

		return ss.str();
	}

	inline std::string ToString(DirectX::XMFLOAT4 *vector)
	{
		std::stringstream ss;

		ss << std::setprecision(7);

		ss << "[ " << vector->x << " " << vector->y << " " << vector->z << " " << vector->w << " ]";

		return ss.str();
	}

	inline std::string ToString(DirectX::XMFLOAT4X4 *matrix)
	{
		std::stringstream ss;

		ss << "[ " << matrix->_11 << " " << matrix->_12 << " " << matrix->_13 << " " << matrix->_14 << "] ";
		ss << "[ " << matrix->_21 << " " << matrix->_22 << " " << matrix->_23 << " " << matrix->_24 << "] ";
		ss << "[ " << matrix->_31 << " " << matrix->_32 << " " << matrix->_33 << " " << matrix->_34 << "] ";
		ss << "[ " << matrix->_41 << " " << matrix->_42 << " " << matrix->_43 << " " << matrix->_44 << "] ";

		return ss.str();
	}

	inline std::string ToString(DirectX::FXMVECTOR vector)
	{
		DirectX::XMFLOAT3 f3;
		DirectX::XMStoreFloat3(&f3, vector);

		return ToString(&f3);
	}

	inline std::string ToString(D3D_DRIVER_TYPE hardware)
	{
		switch (hardware) {

		case D3D_DRIVER_TYPE_UNKNOWN: return "D3D_DRIVER_TYPE_UNKNOWN";
		case D3D_DRIVER_TYPE_HARDWARE: return "D3D_DRIVER_TYPE_HARDWARE";
		case D3D_DRIVER_TYPE_REFERENCE: return "D3D_DRIVER_TYPE_REFERENCE";
		case D3D_DRIVER_TYPE_NULL: return "D3D_DRIVER_TYPE_NULL";
		case D3D_DRIVER_TYPE_SOFTWARE: return "D3D_DRIVER_TYPE_SOFTWARE";
		case D3D_DRIVER_TYPE_WARP: return "D3D_DRIVER_TYPE_WARP";

		default: return "What a #%@$";
		}
	}

	inline std::string ToString(D3D_FEATURE_LEVEL feature)
	{
		switch (feature) {

		case D3D_FEATURE_LEVEL_11_1: return "D3D_FEATURE_LEVEL_11_1";
		case D3D_FEATURE_LEVEL_11_0: return "D3D_FEATURE_LEVEL_11_0";
		case D3D_FEATURE_LEVEL_10_1: return "D3D_FEATURE_LEVEL_10_1";
		case D3D_FEATURE_LEVEL_10_0: return "D3D_FEATURE_LEVEL_10_0";
		case D3D_FEATURE_LEVEL_9_3: return "D3D_FEATURE_LEVEL_9_3";
		case D3D_FEATURE_LEVEL_9_2: return "D3D_FEATURE_LEVEL_9_2";
		case D3D_FEATURE_LEVEL_9_1: return "D3D_FEATURE_LEVEL_9_1";

		default: return "What a #%@$";
		}
	}

	inline std::string ToString(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		switch (topology) {

		default: return "What a #%@$";

		case D3D_PRIMITIVE_TOPOLOGY_UNDEFINED: return "D3D_PRIMITIVE_TOPOLOGY_UNDEFINED";

		case D3D_PRIMITIVE_TOPOLOGY_POINTLIST: return "D3D_PRIMITIVE_TOPOLOGY_POINTLIST";
		case D3D_PRIMITIVE_TOPOLOGY_LINELIST: return "D3D_PRIMITIVE_TOPOLOGY_LINELIST";
		case D3D_PRIMITIVE_TOPOLOGY_LINESTRIP: return "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP";

		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST: return "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST";
		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP: return "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP";

		case D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ: return "D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ";
		case D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ: return "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ";
		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ: return "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ";
		case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ: return "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ";

		// Add *_1_CONTROL_POINT_PATCHLIST   

		}
	}

#endif

}