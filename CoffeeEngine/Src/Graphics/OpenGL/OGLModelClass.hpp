//--------------------------------------------------------------------------------------
// Description: The OpenGL model class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _OGL_MODEL_CLASS_H_
#define _OGL_MODEL_CLASS_H_

#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/ModelClass.hpp"
#include "OGLCommon.hpp"

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class OGLModelClass : public ModelClass
			{
			public:
			
				OGLModelClass() = delete;
				OGLModelClass(const BaseGraphicsClass* pBaseGraphicsClass);
				OGLModelClass(const OGLModelClass& object);
				virtual ~OGLModelClass();

				/// <summary>
				/// Attempts to initialize the model object.
				/// </summary>
				bool Initialize();

				/// <summary>
				/// Begin rendering the model.
				/// </summary>
				void Render(IShader* pShader, float fElapsedTime);

				/// <summary>
				/// Begins the process of cleaning up the model.
				/// </summary>
				void Shutdown();

				/// <summary>
				/// Rotate the object among one or more of the 3-axises.
				/// </summary>
				void Rotate(float x, float y, float z);

				/// <summary>
				/// Translate the object among one or more of the 3-axises.
				/// </summary>
				void Translate(float x, float y, float z);

				/// <summary>
				/// Scale the object among one or more of the 3-axises.
				/// </summary>
				void Scale(float x, float y, float z);

			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				//Primitives
				int m_nVertexCount = 0, m_nIndexCount = 0;

				//Vertex buffers.
				//GLuint m_vaoID[2];
				//GLuint m_vboID[2];
				GLuint VBO;
				GLuint VAO;

			};
		};
	};
};

#endif
