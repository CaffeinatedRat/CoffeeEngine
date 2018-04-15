//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for DirectX.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _GRAPHICS_COMMON_H_
#define _GRAPHICS_COMMON_H_

namespace CoffeeEngine
{
	namespace Graphics
	{
		enum class GraphicsFactoryTypes
		{
			DIRECTX,
			OPENGL
		};

		struct GRAPHICS_VERSION
		{
			int nMajor = 0;
			int nMinor = 0;
		};

		struct GRAPHICS_INITIALIZATION_PARAMETERS
		{
			int nScreenHeight = 640;
			int nScreenWidth = 480;
			int nColorBits = 32;
			int nDepthBits = 32;
			bool bVsync = false;
			float fScreenDepth;
			float fScreenNear;
			bool bFullscreen = false;
			GRAPHICS_VERSION version;
		};
	}
}

#endif
