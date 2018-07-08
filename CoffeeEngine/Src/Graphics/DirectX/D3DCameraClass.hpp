//--------------------------------------------------------------------------------------
// Description: The D3D camera class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#pragma once
#ifndef _D3D_CAMERA_CLASS_H_
#define _D3D_CAMERA_CLASS_H_

#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/CameraClass.hpp"

#include "Graphics/DirectX/D3DCommon.hpp"

using namespace CoffeeEngine::Graphics;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX
		{
			class D3DCameraClass : public CameraClass
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
				
				//Direct3d
				XMMATRIX m_viewMatrix;
				XMMATRIX m_projectionMatrix;
				XMMATRIX m_worldMatrix;

			public:
			
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				D3DCameraClass() = delete;
				D3DCameraClass(const BaseGraphicsClass* pBaseGraphicsClass);
				D3DCameraClass(const D3DCameraClass& object);
				virtual ~D3DCameraClass();

				bool Initialize();
				void Render(float fElapsedTime);
				void Shutdown();

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////

				inline XMMATRIX& GetProjectionMatrix() { return m_projectionMatrix; }
				inline XMMATRIX& GetWorldMatrix() { return m_worldMatrix; }
				inline XMMATRIX& GetViewMatrix() { return m_viewMatrix; }
			};
		}
	};
};

#endif

#endif
