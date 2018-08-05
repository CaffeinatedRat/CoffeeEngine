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
				//                OGL Specific methods
				// 
				////////////////////////////////////////////////////////////

				inline const glm::mat4& GetProjectionMatrix() { return m_projectionMatrix; }
				inline const glm::mat4& GetWorldMatrix() { return m_worldMatrix; }
				inline const glm::mat4& GetViewMatrix() { return m_viewMatrix; }

			private:
				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				glm::vec3 m_positionVector;
				glm::vec3 m_lookAtVector;
				glm::vec3 m_upVector;

				//Primitives
				float m_positionX = 0.0f, m_positionY = 0.0f, m_positionZ = 0.0f;
				float m_rotationX = 0.0f, m_rotationY = 0.0f, m_rotationZ = 0.0f;

				//OGL
				glm::mat4 m_viewMatrix;
				glm::mat4 m_projectionMatrix;
				glm::mat4 m_worldMatrix = glm::mat4(1.0f);
			};
		}
	};
};

#endif
