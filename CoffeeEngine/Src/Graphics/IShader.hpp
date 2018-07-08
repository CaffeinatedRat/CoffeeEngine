//--------------------------------------------------------------------------------------
// Description: The shader interface.  Used to provide a light-weight skeleton to prevent circuluar references for the graphic classes.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _ISHADER_INTERFACE_H_
#define _ISHADER_INTERFACE_H_

#pragma once

#include "Common.hpp"

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
			virtual bool Initialize(const std::string&) = 0;

			/// <summary>
			/// Begin rendering the shader.
			/// </summary>
			virtual void Render(float) = 0;

			/// <summary>
			/// Begins the process of cleaning up the shader.
			/// </summary>
			virtual void Shutdown() = 0;
		};
	};
};

#endif
