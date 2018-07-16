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

#include "D3DCommon.hpp"

using namespace CoffeeEngine::Graphics;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX
		{
			class D3DCameraClass : public CameraClass
			{
			public:

				D3DCameraClass() = delete;
				D3DCameraClass(const BaseGraphicsClass* pBaseGraphicsClass);
				D3DCameraClass(const D3DCameraClass& object);
				virtual ~D3DCameraClass();

				bool Initialize();
				void Render(float fElapsedTime);
				void Shutdown();

				/// <summary>
				/// Sets the vector position of the camera.
				/// </summary>
				inline void SetPosition(float x, float y, float z) override { SetPosition(Vector3(x, y, z)); }
				void SetPosition(const Vector3& vector) override;
				void SetPosition(Vector3&& vector) override;

				/// <summary>
				/// Sets the lookat vector of the camera.
				/// </summary>
				void SetLookAt(float x, float y, float z) override { SetLookAt(Vector3(x, y, z)); }
				void SetLookAt(const Vector3& vector) override;
				void SetLookAt(Vector3&& vector) override;

				/// <summary>
				/// Sets the up vector of the camera.
				/// </summary>
				void SetUp(float x, float y, float z)  override { SetUp(Vector3(x, y, z)); }
				void SetUp(const Vector3& vector) override;
				void SetUp(Vector3&& vector) override;

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////

				inline const XMMATRIX& GetProjectionMatrix() { return m_projectionMatrix; }
				inline const XMMATRIX& GetWorldMatrix() { return m_worldMatrix; }
				inline const XMMATRIX& GetViewMatrix() { return m_viewMatrix; }

			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				XMVECTOR m_positionVector;
				XMVECTOR m_lookAtVector;
				XMVECTOR m_upVector;

				//Direct3d
				XMMATRIX m_viewMatrix;
				XMMATRIX m_projectionMatrix;
				XMMATRIX m_worldMatrix;
			};
		}
	};
};

#endif

#endif
