//--------------------------------------------------------------------------------------
// Description: The OpenGL camera class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _OGL_CAMERA_CLASS_H_
#define _OGL_CAMERA_CLASS_H_

#include "Common.h"
#include "Graphics/BaseGraphicsClass.h"
#include "Graphics/CameraClass.h"

#include "Graphics/OpenGL/OGLCommon.h"

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
				float m_positionX, m_positionY, m_positionZ;
				float m_rotationX, m_rotationY, m_rotationZ;
				
			private:
				OGLCameraClass();

			public:
			
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				OGLCameraClass(BaseGraphicsClass* pBaseGraphicsClass);
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