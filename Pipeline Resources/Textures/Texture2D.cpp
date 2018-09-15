
//
//	Texture2D.cpp
//  Encaspulating a 2D texture, a shader resource view and a sampler state
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Texture2D.h"
#include "..\..\Core\Common\DirectXHelper.h"

using namespace std;
using namespace vxe;

using namespace concurrency;

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;
using namespace Windows::System;

using namespace DirectX;
using namespace DX;

task<void> Texture2D::CreateAsync(const wstring& filename, unsigned pitch, unsigned slicepitch)
{
	DebugPrint(wstring(L"\t Texture2D::CreateAsync()  ...\n" + filename + L"...\n"));

	return create_task(ReadDataAsync(filename)).then([this, pitch, slicepitch](const vector<byte> data) {

		DebugPrint(string("\t -- A lambda: Creating a Texture2D \n"));

		D3D11_SUBRESOURCE_DATA srd = { 0 };
		srd.pSysMem = &data[0];
		srd.SysMemPitch = pitch;
		srd.SysMemSlicePitch = slicepitch;

		ThrowIfFailed(_device->CreateTexture2D(
			&_description,
			&srd,
			&_texture), __FILEW__, __LINE__);

		DebugPrint(std::string("\t -- A lambda: A Texture2D created. \n"));
	});
}

// The wrappers for DirectX Tool Kit WIC functions
void Texture2D::CreateWIC(_In_opt_ ID3D11DeviceContext* context,
	_In_z_ const std::wstring& filename,
	_In_ size_t maxsize)
{
	DebugPrint(wstring(L"\t Texture2D::CreateWIC() from " + filename + L"...\n"));

	ThrowIfFailed(
		CreateWICTextureFromFile(_device.Get(),
		context,
		filename.c_str(),
		violent_cast<ID3D11Resource**>(_texture.GetAddressOf()),
		_srv.GetAddressOf(),
		maxsize), __FILEW__, __LINE__);

	_texture->GetDesc(&_description);

	DebugPrint(string("\t -- A lambda: A Texture2D created. \n"));
}

void Texture2D::CreateDDS(ID3D11DeviceContext* context,
	_In_z_ const std::wstring& filename,
	_In_ size_t maxsize,
	_Out_opt_ DirectX::DDS_ALPHA_MODE* alphamode)
{
	DebugPrint(wstring(L"\t Texture2D::CreateDDS() from " + filename + L"...\n"));

	ThrowIfFailed(
		CreateDDSTextureFromFile(_device.Get(),
		context,
		filename.c_str(),
		violent_cast<ID3D11Resource**>(_texture.GetAddressOf()),
		_srv.GetAddressOf(),
		maxsize,
		alphamode), __FILEW__, __LINE__);

	_texture->GetDesc(&_description);
}

task<void> Texture2D::CreateDDSAsync(_In_opt_ ID3D11DeviceContext* context,
	_In_z_ const wstring& filename,
	_In_ size_t maxsize,
	_Out_opt_ DDS_ALPHA_MODE* alphamode)
{
	DebugPrint(wstring(L"\t Texture2D::CreateDDSAsync() " + filename + L"...\n"));

	return create_task(ReadDataAsync(filename)).then([this, context, maxsize, alphamode](const vector<byte> data) {

		DebugPrint(string("\t -- A lambda: Creating a Texture2D ... \n"));

		ThrowIfFailed(
			CreateDDSTextureFromMemory(_device.Get(),
			context,
			&data[0],
			data.size(),
			violent_cast<ID3D11Resource**>(_texture.GetAddressOf()),
			_srv.GetAddressOf(),
			maxsize,
			alphamode), __FILEW__, __LINE__);

		_texture->GetDesc(&_description);

		DebugPrint(string("\t -- A lambda: A Texture2D created. \n"));
	});
}
