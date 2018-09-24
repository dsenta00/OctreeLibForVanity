
//
//	Resource Factory.cpp
//  A singleton factory for creating various resources and views
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "Resource Factory.h"

using namespace std;

std::unique_ptr<vxe::ResourceFactory> vxe::ResourceFactory::_instance = nullptr;
std::once_flag vxe::ResourceFactory::_flag;

void vxe::ResourceFactory::CreateShaderResourceView(_In_ ID3D11Device2* device, 
	_In_ ID3D11Resource* resource, 
	CD3D11_SHADER_RESOURCE_VIEW_DESC *desc, 
	ID3D11ShaderResourceView **pp)
{
	DebugPrint(string("\t\t ResourceFactory::CreateShaderResourceView() ...\n"));

	ThrowIfFailed(device->CreateShaderResourceView(resource, desc, pp), __FILEW__, __LINE__);
}

void vxe::ResourceFactory::CreateUnorderedAccessView(_In_ ID3D11Device2* device, 
	_In_ ID3D11Resource* resource, 
	CD3D11_UNORDERED_ACCESS_VIEW_DESC *desc, 
	ID3D11UnorderedAccessView **pp)
{
	DebugPrint(string("\t\t ResourceFactory::CreateUnorderedAccessView() ...\n"));

	ThrowIfFailed(device->CreateUnorderedAccessView(resource, desc, pp), __FILEW__, __LINE__);
}