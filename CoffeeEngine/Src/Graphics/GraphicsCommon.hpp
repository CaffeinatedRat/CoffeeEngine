//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for the graphics classes.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _GRAPHICS_COMMON_H_
#define _GRAPHICS_COMMON_H_

namespace CoffeeEngine
{
	namespace Graphics
	{
		enum class GraphicsAPIType
		{
			DIRECTX,
			OPENGL
		};

		struct GRAPHICS_VERSION
		{
			int nMajor = 0;
			int nMinor = 0;
		};

		struct GRAPHICS_PRESENTATION_PROPERTIES
		{
			int screenHeight = 0;
			int screenWidth = 0;
			int colorBits = 0;
			int depthBits = 0;
			int alphaBits = 0;
			int stencilBits = 0;
			int numberOfSamples = 0;
			bool vsyncEnabled = false;
			float screenDepth = 0.0f;
			float screenNear = 0.0f;
			bool fullscreen = false;
			GRAPHICS_VERSION version;
		};
	}
}

#endif
