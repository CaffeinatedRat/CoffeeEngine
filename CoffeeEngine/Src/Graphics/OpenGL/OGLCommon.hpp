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

#ifdef FORCE_LHS
#define GLM_FORCE_LEFT_HANDED
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
		inline glm::vec4 vec4(Vector3 v, float f) { return glm::vec4(v._x, v._y, v._z, f);  }
		inline glm::vec4 vec4(Vector4 v) { return glm::vec4(v._x, v._y, v._z, v._w); }
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



