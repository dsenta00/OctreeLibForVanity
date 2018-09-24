
//
//	DeviceResources.cpp
//  Defining a type for managing the pipeline
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "pch.h"

#include "..\..\Utilities.h"
#include "..\..\Helpers.h"

#include "DeviceResources.h"
#include "DirectXHelper.h"
#include "SwapChainDescription.h"

#include "..\..\Pipeline Stages\State Factory.h"
#include "..\..\Pipeline Resources\Resource Factory.h"

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Controls;
using namespace Platform;

using namespace vxe;
using namespace std;

// Constants used to calculate screen rotations
namespace ScreenRotation
{
	// 0-degree Z-rotation
	static const XMFLOAT4X4 Rotation0(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// 90-degree Z-rotation
	static const XMFLOAT4X4 Rotation90(
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// 180-degree Z-rotation
	static const XMFLOAT4X4 Rotation180(
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// 270-degree Z-rotation
	static const XMFLOAT4X4 Rotation270(
		0.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
};

// Constructor for DeviceResources.
DX::DeviceResources::DeviceResources() :
m_screenViewport(),
m_d3dFeatureLevel(D3D_FEATURE_LEVEL_9_1),
m_d3dRenderTargetSize(),
m_outputSize(),
m_logicalSize(),
m_nativeOrientation(DisplayOrientations::None),
m_currentOrientation(DisplayOrientations::None),
m_dpi(-1.0f),
m_deviceNotify(nullptr)
{
	DebugPrint(string("\t\t DeviceResources::Ctor ...\n"));

	CreateDeviceIndependentResources();
	CreateDeviceResources();
}

// Configures resources that don't depend on the Direct3D device.
void DX::DeviceResources::CreateDeviceIndependentResources()
{
	DebugPrint(string("\t\t DeviceResources::CreateDeviceIndependentResources() ...\n"));

	// Initialize Direct2D resources.
	D2D1_FACTORY_OPTIONS options{};
	//ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
	// If the project is in a debug build, enable Direct2D debugging via SDK Layers.
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	// Initialize the Direct2D Factory.
	ThrowIfFailed(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		__uuidof(ID2D1Factory2),
		&options,
		&m_d2dFactory), __FILEW__, __LINE__);

	// Initialize the DirectWrite Factory.
	ThrowIfFailed(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory2),
		&m_dwriteFactory), __FILEW__, __LINE__);

	// Initialize the Windows Imaging Component (WIC) Factory.
	ThrowIfFailed(CoCreateInstance(CLSID_WICImagingFactory,
		nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_wicFactory)), __FILEW__, __LINE__);
}

// Configures the Direct3D device, and stores handles to it and the device context.
void DX::DeviceResources::CreateDeviceResources()
{
	DebugPrint(string("\t\t DeviceResources::CreateDeviceResources() ...\n"));

	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	if (DX::SdkLayersAvailable())
	{
		// If the project is in a debug build, enable debugging via SDK Layers with this flag.
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	}
#endif

	// This array defines the set of DirectX hardware feature levels this app will support.
	// Note the ordering should be preserved.
	// Don't forget to declare your application's minimum required feature level in its
	// description.  All applications are assumed to support 9.1 unless otherwise stated.
	// There is no 11.2 feature level as of yet
	array<D3D_FEATURE_LEVEL, 7> featurelevels = {
		//D3D_FEATURE_LEVEL_11_2,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// Create the Direct3D 11 API device object and a corresponding context.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	D3D_DRIVER_TYPE	drivertype = D3D_DRIVER_TYPE_HARDWARE;

	HRESULT hr = D3D11CreateDevice(
		nullptr,					// Specify nullptr to use the default adapter.
		drivertype,					// Create a device using the hardware graphics driver.
		0,							// Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
		creationFlags,				// Set debug and Direct2D compatibility flags.
		featurelevels.data(),				// List of feature levels this app can support.
		(unsigned) featurelevels.size(),	// Size of the list above.
		D3D11_SDK_VERSION,			// Always set this to D3D11_SDK_VERSION for Windows Store apps.
		&device,					// Returns the Direct3D device created.
		&m_d3dFeatureLevel,			// Returns feature level of device created.
		&context					// Returns the device immediate context.
		);

	if (FAILED(hr))
	{
		drivertype = D3D_DRIVER_TYPE_WARP;

		// If the initialization fails, fall back to the WARP device.
		// For more information on WARP, see: 
		// http://go.microsoft.com/fwlink/?LinkId=286690
		ThrowIfFailed(
			D3D11CreateDevice(
			nullptr,
			drivertype, // Create a WARP device instead of a hardware device.
			0,
			creationFlags,
			featurelevels.data(),
			(unsigned) featurelevels.size(),
			D3D11_SDK_VERSION,
			&device,
			&m_d3dFeatureLevel,
			&context
			), __FILEW__, __LINE__);
	}

	// Store pointers to the Direct3D 11.1 API device and immediate context.
	ThrowIfFailed(device.As(&m_d3dDevice), __FILEW__, __LINE__);

	ThrowIfFailed(context.As(&m_d3dContext), __FILEW__, __LINE__);

	// Create the Direct2D device object and a corresponding context.
	ComPtr<IDXGIDevice3> dxgiDevice;
	ThrowIfFailed(m_d3dDevice.As(&dxgiDevice), __FILEW__, __LINE__);

	ThrowIfFailed(m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice), __FILEW__, __LINE__);

	ThrowIfFailed(m_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_d2dContext), __FILEW__, __LINE__);

	DebugPrint(string("\t\t\t Driver Type: ") + ToString(drivertype) + string("\n"));
	DebugPrint("\t\t\t Feature Level: " + ToString(m_d3dFeatureLevel) + "\n");
}

void DX::DeviceResources::SetRasterizerState()
{
	if (m_window.Get() != nullptr) {

		Windows::UI::Core::CoreVirtualKeyStates KeyState;

		// Arrow keys
		KeyState = m_window->GetAsyncKeyState(Windows::System::VirtualKey::F1);
		if (bool(KeyState & CoreVirtualKeyStates::Down))
		{
			//DebugPrint(string("\t\t DeviceResources::SetRasterizerState() F1 pressed...\n"));

			StateFactory::Instance().CreateRasterizerState(m_d3dDevice.Get(), 
				D3D11_FILL_WIREFRAME, 
				D3D11_CULL_NONE, 
				false, 
				&_rasterizerstate);

			m_d3dContext->RSSetState(_rasterizerstate.Get());
		}

		KeyState = m_window->GetAsyncKeyState(Windows::System::VirtualKey::F2);
		if (bool(KeyState & CoreVirtualKeyStates::Down))
		{
			//DebugPrint(string("\t\t DeviceResources::SetRasterizerState() F2 pressed...\n"));

			StateFactory::Instance().CreateRasterizerState(m_d3dDevice.Get(), 
				D3D11_FILL_SOLID, 
				D3D11_CULL_BACK, 
				false, 
				&_rasterizerstate);

			m_d3dContext->RSSetState(_rasterizerstate.Get());
		}

		KeyState = m_window->GetAsyncKeyState(Windows::System::VirtualKey::F3);
		if (bool(KeyState & CoreVirtualKeyStates::Down))
		{
			//DebugPrint(string("\t\t DeviceResources::SetRasterizerState() F3 pressed...\n"));

			StateFactory::Instance().CreateRasterizerState(m_d3dDevice.Get(), 
				D3D11_FILL_SOLID, 
				D3D11_CULL_FRONT, 
				false, 
				&_rasterizerstate);

			m_d3dContext->RSSetState(_rasterizerstate.Get());
		}

		KeyState = m_window->GetAsyncKeyState(Windows::System::VirtualKey::F4);
		if (bool(KeyState & CoreVirtualKeyStates::Down))
		{
			//DebugPrint(string("\t\t DeviceResources::SetRasterizerState() F4 pressed...\n"));

			StateFactory::Instance().CreateRasterizerState(m_d3dDevice.Get(), 
				D3D11_FILL_SOLID, 
				D3D11_CULL_NONE, 
				false, 
				&_rasterizerstate);

			m_d3dContext->RSSetState(_rasterizerstate.Get());
		}
	}
}

ID3D11RasterizerState1* DX::DeviceResources::CreateRasterizerState(D3D11_FILL_MODE fill, D3D11_CULL_MODE cull, bool fccw)
{
	ID3D11RasterizerState1* state;
	StateFactory::Instance().CreateRasterizerState(m_d3dDevice.Get(), fill, cull, fccw, &state);

	return state;
}

void DX::DeviceResources::SetBlenderState()
{
	StateFactory::Instance().CreatBlendState(m_d3dDevice.Get(), &_blendstate);
	m_d3dContext->OMSetBlendState(_blendstate.Get(), 0, 0xFFFFFFFF);
}

// These resources need to be recreated every time the window size is changed.
void DX::DeviceResources::CreateWindowSizeDependentResources()
{
	DebugPrint(string("\t\t DeviceResources::CreateWindowSizeDependentResources() ...\n"));

	// Clear the previous window size specific context.
	ID3D11RenderTargetView* nullViews [] = { nullptr };
	m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
	m_d3dRenderTargetView = nullptr;
	m_d2dContext->SetTarget(nullptr);
	m_d2dTargetBitmap = nullptr;
	m_d3dDepthStencilView = nullptr;
	m_d3dContext->Flush();

	// Calculate the necessary render target size in pixels.
	m_outputSize.Width = DX::ConvertDipsToPixels(m_logicalSize.Width, m_dpi);
	m_outputSize.Height = DX::ConvertDipsToPixels(m_logicalSize.Height, m_dpi);

	// Prevent zero size DirectX content from being created.
	m_outputSize.Width = max(m_outputSize.Width, 1.0f);
	m_outputSize.Height = max(m_outputSize.Height, 1.0f);

	// The width and height of the swap chain must be based on the window's
	// natively-oriented width and height. If the window is not in the native
	// orientation, the dimensions must be reversed.
	DXGI_MODE_ROTATION displayRotation = ComputeDisplayRotation();

	bool swapDimensions = displayRotation == DXGI_MODE_ROTATION_ROTATE90 || displayRotation == DXGI_MODE_ROTATION_ROTATE270;
	m_d3dRenderTargetSize.Width = swapDimensions ? m_outputSize.Height : m_outputSize.Width;
	m_d3dRenderTargetSize.Height = swapDimensions ? m_outputSize.Width : m_outputSize.Height;

	if (m_swapChain != nullptr)
	{
		DebugPrint(string("\t\t\t Resizing the swap chain ...\n"));

		// If the swap chain already exists, resize it.
		HRESULT hr = m_swapChain->ResizeBuffers(
			2, // Double-buffered swap chain.
			lround(m_d3dRenderTargetSize.Width),
			lround(m_d3dRenderTargetSize.Height),
			DXGI_FORMAT_B8G8R8A8_UNORM,
			0
			);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			// If the device was removed for any reason, a new device and swap chain will need to be created.
			HandleDeviceLost();

			// Everything is set up now. Do not continue execution of this method. HandleDeviceLost will reenter this method 
			// and correctly set up the new device.
			return;
		}
		else { ThrowIfFailed(hr, __FILEW__, __LINE__); }

	}
	else {
		DebugPrint(string("\t\t\t Creating a new swap chain ...\n"));

		// Otherwise, create a new one using the same adapter as the existing Direct3D device.
		SwapChainDescription swapChainDesc(m_d3dRenderTargetSize.Width, m_d3dRenderTargetSize.Height);

		// This sequence obtains the DXGI factory that was used to create the Direct3D device above.
		ComPtr<IDXGIDevice3> dxgiDevice;
		ThrowIfFailed(m_d3dDevice.As(&dxgiDevice), __FILEW__, __LINE__);

		ComPtr<IDXGIAdapter> dxgiAdapter;
		ThrowIfFailed(dxgiDevice->GetAdapter(&dxgiAdapter), __FILEW__, __LINE__);

		ComPtr<IDXGIFactory2> dxgiFactory;
		ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory)), __FILEW__, __LINE__);

		ThrowIfFailed(dxgiFactory->CreateSwapChainForCoreWindow(m_d3dDevice.Get(),
			reinterpret_cast<IUnknown*>(m_window.Get()),
			swapChainDesc.Get(),
			nullptr, &m_swapChain), __FILEW__, __LINE__);

		// Ensure that DXGI does not queue more than one frame at a time. This both reduces latency and
		// ensures that the application will only render after each VSync, minimizing power consumption.
		ThrowIfFailed(dxgiDevice->SetMaximumFrameLatency(1), __FILEW__, __LINE__);
	}

	// Set the proper orientation for the swap chain, and generate 2D and
	// 3D matrix transformations for rendering to the rotated swap chain.
	// Note the rotation angle for the 2D and 3D transforms are different.
	// This is due to the difference in coordinate spaces.  Additionally,
	// the 3D matrix is specified explicitly to avoid rounding errors.

	switch (displayRotation)
	{
	case DXGI_MODE_ROTATION_IDENTITY:
		m_orientationTransform2D = Matrix3x2F::Identity();
		m_orientationTransform3D = ScreenRotation::Rotation0;
		break;

	case DXGI_MODE_ROTATION_ROTATE90:
		m_orientationTransform2D =
			Matrix3x2F::Rotation(90.0f) *
			Matrix3x2F::Translation(m_logicalSize.Height, 0.0f);
		m_orientationTransform3D = ScreenRotation::Rotation270;
		break;

	case DXGI_MODE_ROTATION_ROTATE180:
		m_orientationTransform2D =
			Matrix3x2F::Rotation(180.0f) *
			Matrix3x2F::Translation(m_logicalSize.Width, m_logicalSize.Height);
		m_orientationTransform3D = ScreenRotation::Rotation180;
		break;

	case DXGI_MODE_ROTATION_ROTATE270:
		m_orientationTransform2D =
			Matrix3x2F::Rotation(270.0f) *
			Matrix3x2F::Translation(0.0f, m_logicalSize.Width);
		m_orientationTransform3D = ScreenRotation::Rotation90;
		break;

	default:
		throw ref new FailureException();
	}

	ThrowIfFailed(m_swapChain->SetRotation(displayRotation), __FILEW__, __LINE__);

	// Create a render target view of the swap chain back buffer.
	ResourceFactory::Instance().CreateRenderTargetView(m_d3dDevice.Get(), m_swapChain.Get(), nullptr, &m_d3dRenderTargetView);

	CD3D11_TEXTURE2D_DESC t2desc(DXGI_FORMAT_D24_UNORM_S8_UINT,
		lround(m_d3dRenderTargetSize.Width),
		lround(m_d3dRenderTargetSize.Height),
		1, 1, D3D11_BIND_DEPTH_STENCIL);

	ResourceFactory::Instance().CreateDepthStencilView(m_d3dDevice.Get(), &t2desc, &m_d3dDepthStencilView);

	// Set the 3D rendering viewport to target the entire window.
	m_screenViewport = CD3D11_VIEWPORT{ 0.0f, 0.0f, m_d3dRenderTargetSize.Width, m_d3dRenderTargetSize.Height };

	m_d3dContext->RSSetViewports(1, &m_screenViewport);

	// Create a Direct2D target bitmap associated with the
	// swap chain back buffer and set it as the current target.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
		m_dpi,
		m_dpi
		);

	ResourceFactory::Instance().CreateTargetBitmap(m_swapChain.Get(), m_d2dContext.Get(), &bitmapProperties, &m_d2dTargetBitmap);
	m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());

	// Grayscale text anti-aliasing is recommended for all Windows Store apps.
	m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
}

// This method is called when the CoreWindow is created (or re-created).
void DX::DeviceResources::SetWindow(CoreWindow^ window)
{
	DebugPrint(string("\t\t DeviceResources::SetWindow() ... \n"));

	DisplayInformation^ currentDisplayInformation = DisplayInformation::GetForCurrentView();

	m_window = window;
	m_logicalSize = Windows::Foundation::Size(window->Bounds.Width, window->Bounds.Height);
	m_nativeOrientation = currentDisplayInformation->NativeOrientation;
	m_currentOrientation = currentDisplayInformation->CurrentOrientation;
	m_dpi = currentDisplayInformation->LogicalDpi;
	m_d2dContext->SetDpi(m_dpi, m_dpi);

	CreateWindowSizeDependentResources();
}

// This method is called in the event handler for the SizeChanged event.
void DX::DeviceResources::SetLogicalSize(Windows::Foundation::Size logicalSize)
{
	if (m_logicalSize != logicalSize)
	{
		m_logicalSize = logicalSize;
		CreateWindowSizeDependentResources();
	}
}

// This method is called in the event handler for the DpiChanged event.
void DX::DeviceResources::SetDpi(float dpi)
{
	if (dpi != m_dpi)
	{
		m_dpi = dpi;

		// When the display DPI changes, the logical size of the window (measured in Dips) also changes and needs to be updated.
		m_logicalSize = Windows::Foundation::Size(m_window->Bounds.Width, m_window->Bounds.Height);

		m_d2dContext->SetDpi(m_dpi, m_dpi);
		CreateWindowSizeDependentResources();
	}
}

// This method is called in the event handler for the OrientationChanged event.
void DX::DeviceResources::SetCurrentOrientation(DisplayOrientations currentOrientation)
{
	if (m_currentOrientation != currentOrientation)
	{
		m_currentOrientation = currentOrientation;
		CreateWindowSizeDependentResources();
	}
}

// This method is called in the event handler for the DisplayContentsInvalidated event.
void DX::DeviceResources::ValidateDevice()
{
	// The D3D Device is no longer valid if the default adapter changed since the device
	// was created or if the device has been removed.

	// First, get the information for the default adapter from when the device was created.

	ComPtr<IDXGIDevice3> dxgiDevice;
	ThrowIfFailed(m_d3dDevice.As(&dxgiDevice), __FILEW__, __LINE__);

	ComPtr<IDXGIAdapter> deviceAdapter;
	ThrowIfFailed(dxgiDevice->GetAdapter(&deviceAdapter), __FILEW__, __LINE__);

	ComPtr<IDXGIFactory2> deviceFactory;
	ThrowIfFailed(deviceAdapter->GetParent(IID_PPV_ARGS(&deviceFactory)), __FILEW__, __LINE__);

	ComPtr<IDXGIAdapter1> previousDefaultAdapter;
	ThrowIfFailed(deviceFactory->EnumAdapters1(0, &previousDefaultAdapter), __FILEW__, __LINE__);

	DXGI_ADAPTER_DESC previousDesc;
	ThrowIfFailed(previousDefaultAdapter->GetDesc(&previousDesc), __FILEW__, __LINE__);

	// Next, get the information for the current default adapter.

	ComPtr<IDXGIFactory2> currentFactory;
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&currentFactory)), __FILEW__, __LINE__);

	ComPtr<IDXGIAdapter1> currentDefaultAdapter;
	ThrowIfFailed(currentFactory->EnumAdapters1(0, &currentDefaultAdapter), __FILEW__, __LINE__);

	DXGI_ADAPTER_DESC currentDesc;
	ThrowIfFailed(currentDefaultAdapter->GetDesc(&currentDesc), __FILEW__, __LINE__);

	// If the adapter LUIDs don't match, or if the device reports that it has been removed,
	// a new D3D device must be created.

	if (previousDesc.AdapterLuid.LowPart != currentDesc.AdapterLuid.LowPart ||
		previousDesc.AdapterLuid.HighPart != currentDesc.AdapterLuid.HighPart ||
		FAILED(m_d3dDevice->GetDeviceRemovedReason()))
	{
		// Release references to resources related to the old device.
		dxgiDevice = nullptr;
		deviceAdapter = nullptr;
		deviceFactory = nullptr;
		previousDefaultAdapter = nullptr;

		// Create a new device and swap chain.
		HandleDeviceLost();
	}
}

// Recreate all device resources and set them back to the current state.
void DX::DeviceResources::HandleDeviceLost()
{
	m_swapChain = nullptr;

	if (m_deviceNotify != nullptr)
	{
		m_deviceNotify->OnDeviceLost();
	}

	CreateDeviceResources();
	m_d2dContext->SetDpi(m_dpi, m_dpi);
	CreateWindowSizeDependentResources();

	if (m_deviceNotify != nullptr)
	{
		m_deviceNotify->OnDeviceRestored();
	}
}

// Register our DeviceNotify to be informed on device lost and creation.
void DX::DeviceResources::RegisterDeviceNotify(DX::IDeviceNotify* deviceNotify)
{
	m_deviceNotify = deviceNotify;
}

// Call this method when the app suspends. It provides a hint to the driver that the app 
// is entering an idle state and that temporary buffers can be reclaimed for use by other apps.
void DX::DeviceResources::Trim()
{
	ComPtr<IDXGIDevice3> dxgiDevice;
	m_d3dDevice.As(&dxgiDevice);

	dxgiDevice->Trim();
}

// Present the contents of the swap chain to the screen.
void DX::DeviceResources::Present()
{
	// The first argument instructs DXGI to block until VSync, putting the application
	// to sleep until the next VSync. This ensures we don't waste any cycles rendering
	// frames that will never be displayed to the screen.
	HRESULT hr = m_swapChain->Present(1, 0);

	// Discard the contents of the render target.
	// This is a valid operation only when the existing contents will be entirely
	// overwritten. If dirty or scroll rects are used, this call should be removed.
	m_d3dContext->DiscardView(m_d3dRenderTargetView.Get());

	// Discard the contents of the depth stencil.
	m_d3dContext->DiscardView(m_d3dDepthStencilView.Get());

	// If the device was removed either by a disconnection or a driver upgrade, we 
	// must recreate all device resources.
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		HandleDeviceLost();
	}
	else
	{
		ThrowIfFailed(hr, __FILEW__, __LINE__);
	}
}

// This method determines the rotation between the display device's native Orientation and the
// current display orientation.
DXGI_MODE_ROTATION DX::DeviceResources::ComputeDisplayRotation()
{
	DXGI_MODE_ROTATION rotation = DXGI_MODE_ROTATION_UNSPECIFIED;

	// Note: NativeOrientation can only be Landscape or Portrait even though
	// the DisplayOrientations enum has other values.
	switch (m_nativeOrientation)
	{
	case DisplayOrientations::Landscape:
		switch (m_currentOrientation)
		{
		case DisplayOrientations::Landscape:
			rotation = DXGI_MODE_ROTATION_IDENTITY;
			break;

		case DisplayOrientations::Portrait:
			rotation = DXGI_MODE_ROTATION_ROTATE270;
			break;

		case DisplayOrientations::LandscapeFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE180;
			break;

		case DisplayOrientations::PortraitFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE90;
			break;
		}
		break;

	case DisplayOrientations::Portrait:
		switch (m_currentOrientation)
		{
		case DisplayOrientations::Landscape:
			rotation = DXGI_MODE_ROTATION_ROTATE90;
			break;

		case DisplayOrientations::Portrait:
			rotation = DXGI_MODE_ROTATION_IDENTITY;
			break;

		case DisplayOrientations::LandscapeFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE270;
			break;

		case DisplayOrientations::PortraitFlipped:
			rotation = DXGI_MODE_ROTATION_ROTATE180;
			break;
		}
		break;
	}
	return rotation;
}