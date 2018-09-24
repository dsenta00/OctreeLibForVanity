//
//	FirstPerson Camera.cpp
//	Encapsulates basic camera movements and rotations
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "FirstPerson Camera.h"

using namespace Windows::System;
using namespace vxe;
using namespace DirectX;

const DirectX::XMFLOAT3 FirstPersonCamera::_movevelocity = { 20.0f, 10.f, 10.0f };
const DirectX::XMFLOAT2 FirstPersonCamera::_rotationvelocity = { 0.5f, 0.5f};
const float FirstPersonCamera::_debounce = 2.0f;

void FirstPersonCamera::Update(InputController^ inputcontroller, DX::StepTimer const& timer)
{
	float time = (float) timer.GetElapsedSeconds();

	auto rotationx = XMMatrixRotationX(_alfa);
	auto rotationy = XMMatrixRotationY(_beta);

	_rotation = XMMatrixMultiply(rotationy, rotationx);

	ProcessInput(inputcontroller, time);

	SetView();
};

void FirstPersonCamera::ProcessInput(InputController^ inputcontroller, float time)
{
	auto movement = ProcessKeyboard(inputcontroller, time);

	ProcessPointer(inputcontroller, time);

	auto d = XMVector3Transform(XMLoadFloat3(&movement), _rotation);
	_eye.ChangePosition(XMVectorGetX(d), XMVectorGetY(d), XMVectorGetZ(d));

	auto forward = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	auto eye = _eye.GetValue();
	auto lookat = XMLoadFloat4(&eye) + XMVector3Transform(forward, _rotation);

	_lookat.x = XMVectorGetX(lookat);
	_lookat.y = XMVectorGetY(lookat);
	_lookat.z = XMVectorGetZ(lookat);
}

XMFLOAT3 FirstPersonCamera::ProcessKeyboard(InputController^ inputcontroller, float time)
{
	auto movement = XMFLOAT3(0.0f, 0.0f, 0.0f);

	if (inputcontroller->IsKeyDown(VirtualKey::D))
		movement.x += time * _movevelocity.x;

	if (inputcontroller->IsKeyDown(VirtualKey::A))
		movement.x -= time * _movevelocity.x;

	if (inputcontroller->IsKeyDown(VirtualKey::Q))
		movement.y += time * _movevelocity.y;

	if (inputcontroller->IsKeyDown(VirtualKey::E))
		movement.y -= time * _movevelocity.y;

	if (inputcontroller->IsKeyDown(VirtualKey::W))
		movement.z += time * _movevelocity.z;

	if (inputcontroller->IsKeyDown(VirtualKey::S))
		movement.z -= time * _movevelocity.z; 
	
	return movement;
}

void FirstPersonCamera::ProcessPointer(InputController^ inputcontroller, float time) 
{
	if (!inputcontroller->IsLeftButtonPressed()) return;

	_lastpointerposition = _currentpointerposition;
	_currentpointerposition = inputcontroller->GetPointerPosition();

	if (_currentpointerposition.y - _lastpointerposition.y > _debounce) 
		_alfa += _rotationvelocity.x * time;
	
	else if (_currentpointerposition.y - _lastpointerposition.y < -_debounce)
		_alfa -= _rotationvelocity.x * time;

	else if (_currentpointerposition.x - _lastpointerposition.x > _debounce)
		_beta += _rotationvelocity.y * time;

	else if (_currentpointerposition.x - _lastpointerposition.x < -_debounce)
		_beta -= _rotationvelocity.y * time;

	if (_alfa > 1.4f) _alfa = 1.4f;
	else if (_alfa < -1.4f) _alfa = - 1.4f;

	if (_beta > XM_PI) _beta -= 2 * XM_PI;
	else if (_beta < -XM_PI) _beta += 2 * XM_PI;
}