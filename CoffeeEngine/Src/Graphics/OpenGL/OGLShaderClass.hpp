//--------------------------------------------------------------------------------------
// Description: The OpenGL shader class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
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
			
				//Restricting namespace scoping to within the class.
				using LogLevelType = CoffeeEngine::Utility::Logging::LogLevelType;

				OGLShaderClass() = delete;
				OGLShaderClass(const BaseGraphicsClass* pBaseGraphicsClass);
				OGLShaderClass(const OGLShaderClass& object);
				virtual ~OGLShaderClass();

				virtual bool Initialize(const std::string& sFileName);
				virtual void Render(float fElapsedTime);
				virtual void Shutdown();


				inline void setInt(const char* name, int value) const {
					glUniform1i(glGetUniformLocation(m_programId, name), value);
				}

				inline void setBool(const char* name, bool value) const {
					glUniform1i(glGetUniformLocation(m_programId, name), (int)value);
				}

				inline void setFloat(const char* name, float value) const {
					glUniform1f(glGetUniformLocation(m_programId, name), value);
				}

				inline void setVector2(const char* name, const glm::vec2& vec) const {
					glUniform2fv(glGetUniformLocation(m_programId, name), 1, &vec[0]);
				}

				inline void setVector2(const char* name, float x, float y) const {
					glUniform2f(glGetUniformLocation(m_programId, name), x, y);
				}

				inline void setVector3(const char* name, const glm::vec3& vec) const {
					glUniform3fv(glGetUniformLocation(m_programId, name), 1, &vec[0]);
				}

				inline void setVector3(const char* name, float x, float y, float z) const {
					glUniform3f(glGetUniformLocation(m_programId, name), x, y, z);
				}

				inline void setVector4(const char* name, const glm::vec4& vec) const {
					glUniform4fv(glGetUniformLocation(m_programId, name), 1, &vec[0]);
				}

				inline void setVector4(const char* name, float x, float y, float z, float w) const {
					glUniform4f(glGetUniformLocation(m_programId, name), x, y, z, w);
				}

				inline void setMatrix2(const char* name, glm::mat2& mat) const {
					glUniformMatrix2fv(glGetUniformLocation(m_programId, name), 1, GL_FALSE, &mat[0][0]);
				}

				inline void setMatrix3(const char* name, glm::mat3& mat) const {
					glUniformMatrix3fv(glGetUniformLocation(m_programId, name), 1, GL_FALSE, &mat[0][0]);
				}

				inline void setMatrix4(const char* name, const glm::mat4& mat) const {
					glUniformMatrix4fv(glGetUniformLocation(m_programId, name), 1, GL_FALSE, &mat[0][0]);
				}

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
			private:
				GLuint m_programId = 0;

			};
		};
	};
};

#endif
