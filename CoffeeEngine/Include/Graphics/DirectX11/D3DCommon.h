//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for DirectX.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3D_COMMON_H_
#define _D3D_COMMON_H_

#define SAFE_RELEASE(p) if (p != NULL) { p->Release(); p = NULL; }

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX11
		{
			extern const char* VERTEX_SHADER_VERSION;
			extern const char* PIXEL_SHADER_VERSION;
		}
	}
}

#endif