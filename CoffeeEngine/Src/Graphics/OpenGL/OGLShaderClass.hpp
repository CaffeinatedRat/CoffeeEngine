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

#include "OGLCommon.hpp"
#include "OGLGraphicsClass.hpp"

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class OGLShaderClass : public ShaderClass
			{
			public:
			
				OGLShaderClass() = delete;
				OGLShaderClass(const BaseGraphicsClass* pBaseGraphicsClass);
				OGLShaderClass(const OGLShaderClass& object);
				virtual ~OGLShaderClass();

				virtual bool Initialize(const std::string& sFileName);
				virtual void Render(float fElapsedTime);
				virtual void Shutdown();

			private:
				bool SetShaderParameters(float fElapsedTime);

				/// <summary>
				/// Loads a shader from the file.
				/// </summary>
				GLuint LoadShaderFromFile(std::string, ShaderType);

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////
				GLuint m_programId = 0;

			};
		};
	};
};

#endif
