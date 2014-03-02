//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for OpenGL.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _OGL_COMMON_H_
#define _OGL_COMMON_H_

#define GLEW_STATIC

#include "GL\glew.h"
#include "GL\wglew.h"
#include <gl\glu.h>

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			const float OGL_PI = 3.14159265f;
		}
	}
}

#endif



