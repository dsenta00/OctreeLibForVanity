

#pragma once

//
//	Pointer.h
//  A type for managing the state of the pointer (moudse)
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"

namespace vxe {

	ref class Pointer {

	internal:
		Pointer()
		{
			DebugPrint(std::string("\t Pointer::Ctor... \n"));
		}

		void SetPosition(Windows::Foundation::Point point)
		{
			//DebugPrint(std::string("\t Pointer::SetPosition() Position (" + std::to_string(point.X) + std::string(",") + 
				//std::to_string(point.Y) + std::string(") ...\n")));

			_position.x = point.X;
			_position.y = point.Y;
		}

		DirectX::XMFLOAT2 GetPosition() { return _position; }

		void SetState(Windows::UI::Input::PointerPointProperties^ properties)
		{
			DebugPrint(std::string("\t Pointer::SetState() Properties: \n"));

			_state = properties;

			DebugPrint(std::string("\t\tLeftMousePressed: " + std::to_string (IsLeftButtonPressed()) + "\n"));
			DebugPrint(std::string("\t\tMiddleMousePressed: " + std::to_string(IsMiddleButtonPressed()) + "\n"));
			DebugPrint(std::string("\t\tRightMousePressed: " + std::to_string(IsRightButtonPressed()) + "\n"));
		}

		bool IsLeftButtonPressed() 
		{ 
			if (_state == nullptr) return false;

			return _state->IsLeftButtonPressed;
		}

		bool IsMiddleButtonPressed() 
		{ 
			if (_state == nullptr) return false;

			return _state->IsMiddleButtonPressed;
		}

		bool IsRightButtonPressed() 
		{ 
			if (_state == nullptr) return false;

			return _state->IsRightButtonPressed;
		}

	private:
		DirectX::XMFLOAT2 _position;
		Windows::UI::Input::PointerPointProperties^ _state;
	};

}