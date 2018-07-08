//--------------------------------------------------------------------------------------
// Description: The OpenGL camera class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _OGL_CAMERA_CLASS_H_
#define _OGL_CAMERA_CLASS_H_

#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/CameraClass.hpp"

#include "OGLCommon.hpp"

using namespace CoffeeEngine::Graphics;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class OGLCameraClass : public CameraClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				//Primitives
				float m_positionX = 0.0f, m_positionY = 0.0f, m_positionZ = 0.0f;
				float m_rotationX = 0.0f, m_rotationY = 0.0f, m_rotationZ = 0.0f;
				
			private:
				OGLCameraClass();

			public:
			
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				OGLCameraClass(const BaseGraphicsClass* pBaseGraphicsClass);
				OGLCameraClass(const OGLCameraClass& object);
				virtual ~OGLCameraClass();

				bool Initialize();
				void Render(float fElapsedTime);
				void Shutdown();

			protected:
				void OGLMatrixPerspectiveFovLH(float *m, float fov, float aspect, float znear, float zfar);

			};
		}
	};
};

#endif
