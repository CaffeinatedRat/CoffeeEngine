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
			class OGLCameraClass : public CameraClass<glm::mat4>
			{			
			public:		

				OGLCameraClass() = delete;
				OGLCameraClass(const BaseGraphicsClass* pBaseGraphicsClass);
				OGLCameraClass(const OGLCameraClass& object) noexcept;
				OGLCameraClass(OGLCameraClass&& object) noexcept;
				virtual ~OGLCameraClass();

				OGLCameraClass& operator=(OGLCameraClass&&) = default;
				OGLCameraClass& operator=(const OGLCameraClass&) = default;

				bool Initialize() override;
				void Render(float fElapsedTime) override;
				void Shutdown() override;

				/// <summary>
				/// Updates the graphics properties such as aspect ratio and fov.
				/// </summary>
				void UpdateGraphicsProperties() override;

				/// <summary>
				/// Sets the vector position of the camera.
				/// </summary>
				inline void SetPosition(float x, float y, float z) override { SetPosition(Vector3(x, y, z)); }
				void SetPosition(const Vector3& vector) override;
				void SetPosition(Vector3&& vector) override;

				/// <summary>
				/// Sets the lookat vector of the camera.
				/// </summary>
				inline void SetLookAt(float x, float y, float z) override { SetLookAt(Vector3(x, y, z)); }
				void SetLookAt(const Vector3& vector) override;
				void SetLookAt(Vector3&& vector) override;

				/// <summary>
				/// Sets the up vector of the camera.
				/// </summary>
				inline void SetUp(float x, float y, float z)  override { SetUp(Vector3(x, y, z)); }
				void SetUp(const Vector3& vector) override;
				void SetUp(Vector3&& vector) override;

			private:
				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////
				glm::vec3 m_positionVector;
			};
		}
	};
};

#endif
