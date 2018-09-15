
#pragma once

//
//	Buffer Base.h
//  A base class for DirectX buffers
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

namespace vxe {

	class BufferBase {

	public:
		BufferBase(unsigned size) : _buffer{ nullptr }, _size{ size } {}

		ID3D11Buffer* GetBuffer() { return _buffer.Get(); }

		void Reset()
		{
			DebugPrint(std::string("\t BufferBase::Reset() ...\n"));

			_buffer.Reset();
		}

		~BufferBase() {}

	protected:
		unsigned _size;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
	};

}