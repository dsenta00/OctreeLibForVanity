
#pragma once

//
//	FirstPerson Camera.h
//	Encapsulates basic camera movements and rotations
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\Input\Input Controller.h"

#include "Camera Base.h"

#include "..\..\Core\Common\StepTimer.h"

namespace vxe {

	class FirstPersonCamera : public CameraBase {

	public:
		FirstPersonCamera(_In_ ID3D11Device2* device)
			: CameraBase{ device },
			_alfa{ -0.1f },
			_beta{ 0.0f }
		{
			DebugPrint(std::string("\t FirstPersonCamera::Ctor ...\n"));
		}	

		void Update(InputController^, DX::StepTimer const&);
		
		void ProcessInput(InputController^, float);
		DirectX::XMFLOAT3 ProcessKeyboard(InputController^, float);
		void ProcessPointer(InputController^, float);

	private:
		// Rotations about x and y axis 
		float _alfa;
		float _beta;
		DirectX::XMMATRIX _rotation;
		DirectX::XMFLOAT2 _lastpointerposition;
		DirectX::XMFLOAT2 _currentpointerposition;

		static const DirectX::XMFLOAT3 _movevelocity;
		static const DirectX::XMFLOAT2 _rotationvelocity;
		static const float _debounce;
	};

}