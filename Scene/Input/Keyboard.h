

#pragma once

//
//	Keyboard.h
//  A type for managing the state of the keyboard
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"

namespace vxe {

	ref class Keyboard {

	internal:
		Keyboard() 
		{
			DebugPrint(std::string("\t Keyboard::Ctor...\n"));
		}

		void SetKeyState(Windows::System::VirtualKey key, bool pressed)
		{
			//DebugPrint(std::wstring(L"\t Keyboard::SetKeyState() Key: " + key.ToString() + (pressed ? " Down" : " Up") + L"...\n"));

			_keys[key] = pressed;
		}

		// If there is no key in the map, the default value is inserted into the map
		bool IsKeyDown(Windows::System::VirtualKey key) { return _keys[key] == true; }

		bool IsKeyUp(Windows::System::VirtualKey key) { return _keys[key] == false; }

		void ResetKeyStates()
		{
			for (auto& key : _keys) key.second = false;
		}

		void Clear() { _keys.clear(); }

	private:
		std::map<Windows::System::VirtualKey, bool> _keys;
	};

}