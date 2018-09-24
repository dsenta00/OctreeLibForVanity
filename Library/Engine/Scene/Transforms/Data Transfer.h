
#pragma once

//
//	Data Transfer.h
//  Transfers a data (matrix, vector) via a constant buffer 
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\..\Helpers.h"

#include "..\..\Pipeline Resources\Buffers\Constant Buffer.h"

namespace vxe {

	template <typename T>
	class DataTransfer {

	public:
		using value_type = T;

	public:
		DataTransfer(_In_ ID3D11Device2* device)
			: _buffer{ device }
		{
			DebugPrint(std::string("\t DataTransfer<") + typeid(value_type).name() + std::string(">::Ctor ...\n"));
		}

		T GetValue() { return _transfer; }

		ConstantBuffer<T>* GetConstantBuffer() { return &_buffer; }

		void Update(_In_ ID3D11DeviceContext2* context)
		{
			//DebugPrint(std::string("\t\t DataTransfer::Update() ...\n"));

			_buffer.Update(context, _transfer);
		}

		void Reset()
		{
			DebugPrint(std::string("\t\t DataTransfer::Reset() ...\n"));

			_buffer.Reset();
		}

	protected:
		ConstantBuffer<T> _buffer;
		T _transfer;
	};

}