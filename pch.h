#pragma once

//
//	pch.h
//  Precompiled header files
//
//  © 2015 Vanity DirectX 11.2 Engine (VXE). Zoraja Consulting d.o.o. All rights reserved.
//

#include "targetver.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif

// Windows header files
#define NOMINMAX
#include <windows.h>


// Standard WinRT includes
#include <wrl.h>
#include <wrl/client.h>
#include <agile.h>	// agile.h can only be used with /ZW
#include <concrt.h>

// DirectX 11.2 includes
#include <d3d11_2.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <Third Party/DirectX Tool Kit/VertexTypes.h>

// PPL includes
#include <ppltasks.h>

// Standard C++ includes
#include <assert.h>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <typeinfo>
#include <thread>
#include <mutex>
#include <array>
#include <cmath>
#include <map>
#include <algorithm>
#include <iostream>

typedef DirectX::XMFLOAT3 Pos3;
typedef DirectX::VertexPositionColor Vertex;