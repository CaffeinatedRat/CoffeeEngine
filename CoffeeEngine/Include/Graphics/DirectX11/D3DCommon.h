//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for DirectX.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3D_COMMON_H_
#define _D3D_COMMON_H_

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#define SAFE_RELEASE(p) if (p != NULL) { p->Release(); p = NULL; }

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX11
		{
			extern const char* VERTEX_SHADER_VERSION;
			extern const char* PIXEL_SHADER_VERSION;

			typedef struct SimpleMatrixBufferType
			{
				D3DXMATRIX world;
				D3DXMATRIX view;
				D3DXMATRIX projection;
			} SimpleMatrixBufferType;

			typedef struct SimpleVertexType
			{
				D3DXVECTOR3 position;
				D3DXVECTOR4 color;
				D3DXVECTOR2 texture;
				//D3DXVECTOR3 normal;
			} SimpleVertexType;
		}
	}
}

#endif