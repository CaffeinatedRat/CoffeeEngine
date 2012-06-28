//--------------------------------------------------------------------------------------
// Description: The shader interface.  Used to provide a light-weight skeleton to prevent circuluar references for the graphic classes.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _ISHADER_INTERFACE_H_
#define _ISHADER_INTERFACE_H_

#include "Common.h"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class IShader
		{
		public:

			/// <summary>
			/// Attempts to initialize the shader object.
			/// </summary>
			virtual bool Initialize(std::string sFileName) = 0;

			/// <summary>
			/// Begin rendering the shader.
			/// </summary>
			virtual void Render(float fElapsedTime) = 0;

			/// <summary>
			/// Begins the process of cleaning up the shader.
			/// </summary>
			virtual void Shutdown() = 0;
		};
	};
};

#endif