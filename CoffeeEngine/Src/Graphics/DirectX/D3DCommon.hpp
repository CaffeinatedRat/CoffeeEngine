//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for DirectX.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#pragma once
#ifndef _D3D_COMMON_H_
#define _D3D_COMMON_H_

//#include <dxgi.h>
//#include <d3dcommon.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>

using namespace DirectX;

#define SAFE_RELEASE(p) if (p != nullptr) { p->Release(); p = nullptr; }

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX
		{
			extern const char* VERTEX_SHADER_VERSION;
			extern const char* PIXEL_SHADER_VERSION;

			typedef struct SimpleMatrixBufferType
			{
				XMMATRIX world;
				XMMATRIX view;
				XMMATRIX projection;
			} SimpleMatrixBufferType;

			typedef struct SimpleVertexType
			{
				XMFLOAT3 position;
				XMFLOAT4 color;
				XMFLOAT2 texture;
				//D3DXVECTOR3 normal;
			} SimpleVertexType;
		}
	}
}

#endif

#endif
