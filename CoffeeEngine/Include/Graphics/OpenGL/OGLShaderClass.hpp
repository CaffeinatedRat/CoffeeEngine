//--------------------------------------------------------------------------------------
// Description: The OpenGL shader class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _OGL_SHADER_CLASS_H_
#define _OGL_SHADER_CLASS_H_

#pragma once

#include "Common.hpp"
#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/ShaderClass.hpp"

#include "Graphics/OpenGL/OGLCommon.hpp"
#include "Graphics/OpenGL/OGLGraphicsClass.hpp"

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class OGLShaderClass : public ShaderClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

			private:
				OGLShaderClass();

			public:
			
				OGLShaderClass(const BaseGraphicsClass* pBaseGraphicsClass);
				OGLShaderClass(const OGLShaderClass& object);
				virtual ~OGLShaderClass();

				virtual bool Initialize(const std::string& sFileName);
				virtual void Render(float fElapsedTime);
				virtual void Shutdown();

			private:
				bool SetShaderParameters(float fElapsedTime);
			};
		};
	};
};

#endif
