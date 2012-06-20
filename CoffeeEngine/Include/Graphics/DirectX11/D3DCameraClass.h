//--------------------------------------------------------------------------------------
// Description: The D3D camera class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3D_CAMERA_CLASS_H_
#define _D3D_CAMERA_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\CameraClass.h"

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

using namespace CoffeeEngine::Graphics;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX11
		{
			class D3DCameraClass : public CameraClass
			{
			private:
				D3DCameraClass();

			public:
			
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				D3DCameraClass(BaseGraphicsClass* pBaseGraphicsClass);
				D3DCameraClass(const D3DCameraClass& object);
				virtual ~D3DCameraClass();

				bool Initialize();
				void Shutdown();
				void Render();

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////

				inline D3DXMATRIX& GetProjectionMatrix() { return m_projectionMatrix; }
				inline D3DXMATRIX& GetWorldMatrix() { return m_worldMatrix; }
				inline D3DXMATRIX& GetViewMatrix() { return m_viewMatrix; }

			private:
				float m_positionX, m_positionY, m_positionZ;
				float m_rotationX, m_rotationY, m_rotationZ;
				
				D3DXMATRIX m_viewMatrix;
				D3DXMATRIX m_projectionMatrix;
				D3DXMATRIX m_worldMatrix;
			};
		}
	};
};

#endif