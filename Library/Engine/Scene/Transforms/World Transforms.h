
#pragma once

//
//	World Transforms.h
//  Defining the basic world transforms
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\..\Helpers.h"

#include "Data Transfer.h"

namespace vxe {

	using Transfer = struct Transfer {
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 dlrow;
	};

	class WorldTransforms : public DataTransfer<Transfer> {

	public:
		WorldTransforms(_In_ ID3D11Device2* device) 
			: DataTransfer{ device }
		{
			DebugPrint(std::string("\t WorldTransforms::Ctor ...\n"));

			DirectX::XMMATRIX identity = DirectX::XMMatrixIdentity();

			DirectX::XMStoreFloat4x4(&_transfer.world, identity);
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, identity);

			DebugPrint(std::string("\t\t World: ") + ToString(&_transfer.world) + std::string("\n"));
		}

		void SetWorld(DirectX::XMFLOAT4X4& world) { _transfer.world = world; }
		DirectX::XMFLOAT4X4& GetWorld() { return _transfer.world; }

		void SetDlrow(DirectX::XMFLOAT4X4& dlrow) { _transfer.dlrow = dlrow; }
		DirectX::XMFLOAT4X4& GetDlrow() { return _transfer.dlrow; }

		void Transform(DirectX::CXMMATRIX scale, DirectX::CXMMATRIX rotation, DirectX::CXMMATRIX translation)
		{
			DebugPrint(std::string("\t\t WorldTransforms::Transform() ...\n"));

			DirectX::XMMATRIX world = DirectX::XMMatrixMultiply(DirectX::XMMatrixMultiply(scale, rotation), translation);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}

		void Translate(float x, float y, float z)
		{
			DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(x, y, z);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}

		void Scale(float x, float y, float z)
		{
			DirectX::XMMATRIX world = DirectX::XMMatrixScaling(x, y, z);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}	

		void RotateX(float radians)
		{
			DirectX::XMMATRIX world = DirectX::XMMatrixRotationX(radians);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}

		void RotateY(float radians)
		{
			DirectX::XMMATRIX world = DirectX::XMMatrixRotationY(radians);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}

		void RotateZ(float radians)
		{
			DirectX::XMMATRIX world = DirectX::XMMatrixRotationZ(radians);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}

		void RotateYAndTranslate(float radians, float x = 0, float y = 0, float z = 0)
		{
			DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(x, y, z);
			DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationY(radians);

			DirectX::XMMATRIX world = DirectX::XMMatrixMultiply(rotation, translation);

			DirectX::XMMATRIX dlrow = GetInverseMatrix(world);

			DirectX::XMStoreFloat4x4(&_transfer.world, DirectX::XMMatrixTranspose(world));
			DirectX::XMStoreFloat4x4(&_transfer.dlrow, dlrow);
		}
	};

}