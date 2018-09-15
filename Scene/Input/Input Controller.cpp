
//
//	SimpleInputController.cpp
//  A type for managing input devices (keyboard and pointer)
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Input Controller.h"

using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

using namespace vxe;

void InputController::Initialize(CoreWindow^ window)
{
	DebugPrint(std::string("\t InputController::Initialize() \n"));

	_keyboard = ref new Keyboard();

	window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputController::OnKeyDown);
	window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InputController::OnKeyUp);

	_pointer = ref new Pointer();

	window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);
	window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerPressed);
	window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerReleased);
	window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &InputController::OnPointerMoved);
};

void InputController::ResetSates()
{
	_keyboard->ResetKeyStates();
}

void InputController::Update() { }

void InputController::Clear()
{
	_keyboard->Clear();
}