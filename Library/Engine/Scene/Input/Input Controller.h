
#pragma once

//
//	Input Controller.h
//  A type for managing input devices (keyboard and pointer)
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Keyboard.h"
#include "Pointer.h"

#include "..\..\Utilities.h"

namespace vxe {

	ref class InputController {

	internal:
		InputController()
		{
			DebugPrint(std::string("\t InputController::Ctor... \n"));
		}

		void Initialize(_In_ Windows::UI::Core::CoreWindow^);

	protected:
		void OnKeyDown(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
		{
			_keyboard->SetKeyState(args->VirtualKey, true);
		}

		void OnKeyUp(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args)
		{
			_keyboard->SetKeyState(args->VirtualKey, false);
		}

		void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args)
		{
			_pointer->SetState(args->CurrentPoint->Properties);
		}

		void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args)
		{
			_pointer->SetState(args->CurrentPoint->Properties);
		}

		void OnPointerMoved(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args)
		{
			_pointer->SetPosition(args->CurrentPoint->Position);
		}

	public:
		inline bool IsKeyDown(Windows::System::VirtualKey key) { return _keyboard->IsKeyDown(key); }

		inline bool IsKeyUp(Windows::System::VirtualKey key) { return _keyboard->IsKeyUp (key); }

		inline bool IsLeftButtonPressed() { return _pointer->IsLeftButtonPressed(); }

		inline bool IsMiddleButtonPressed() { return _pointer->IsMiddleButtonPressed(); }

		inline bool IsRightButtonPressed() { return _pointer->IsRightButtonPressed(); }

		void Update();

		void ResetSates();

		void Clear();

	internal:
		DirectX::XMFLOAT2 GetPointerPosition() { return _pointer->GetPosition(); }

	private:
		Keyboard^ _keyboard;
		Pointer^ _pointer;
	};

}