//--------------------------------------------------------------------------------------
// Description: The OpenGL shader class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _OGL_SHADER_CLASS_H_
#define _OGL_SHADER_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\ShaderClass.h"

#include "Graphics\OpenGL\OGLCommon.h"
#include "Graphics\OpenGL\OGLGraphicsClass.h"

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
			
				OGLShaderClass(BaseGraphicsClass* pBaseGraphicsClass);
				OGLShaderClass(const OGLShaderClass& object);
				virtual ~OGLShaderClass();

				virtual bool Initialize(std::string sFileName);
				virtual void Render(float fElapsedTime);
				virtual void Shutdown();

			private:
				bool SetShaderParameters(float fElapsedTime);
			};
		};
	};
};

#endif