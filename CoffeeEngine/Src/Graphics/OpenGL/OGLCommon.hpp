//--------------------------------------------------------------------------------------
// Description: Specific global variables, functions, and definitions for OpenGL.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
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

#ifndef GLM_EXTENSION
#define GLM_EXTENSION 
namespace glm
{
	//Extensions
	namespace ext
	{
		inline glm::vec3 vec3(Vector3 v) { return glm::vec3(v._x, v._y, v._z); }
	}
}
#endif

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
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



