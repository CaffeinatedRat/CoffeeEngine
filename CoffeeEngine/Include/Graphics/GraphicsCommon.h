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
		typedef struct GRAPHICS_INITIALIZATION_PARAMETERS
		{
			int nScreenHeight;
			int nScreenWidth;
			bool bVsync;
			float fScreenDepth;
			float fScreenNear;
			bool bFullscreen;
		} GRAPHICS_INITIALIZATION_PARAMETERS;
	}
}

#endif