//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for OpenGL.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _OGL_COMMON_H_
#define _OGL_COMMON_H_

#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <glm/glm.hpp>
#include <gl/glew.h>
#include <gl/wglew.h>

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			const float OGL_PI = 3.14159265f;

			enum class ShaderType {
				Vertex,
				Fragment,
				Geometry,
				Program
			};
		}
	}
}

#endif



