//--------------------------------------------------------------------------------------
// Description: The base camera class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Common.hpp"
#include "BaseGraphicsClass.hpp"
#include "ICamera.hpp"
#include "Engine/IObject.hpp"

using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Engine;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class CameraClass : public ICamera
		{
		protected:
			const BaseGraphicsClass *m_pGraphicsClass = nullptr;

		public:
			
			CameraClass() = delete;
			CameraClass(const BaseGraphicsClass* pBaseGraphicsClass);
			CameraClass(const CameraClass& object) noexcept;
			CameraClass(CameraClass&& object) noexcept;
			virtual ~CameraClass() { };

			CameraClass& operator=(const CameraClass&) = default;
			CameraClass& operator=(CameraClass&&) = default;

			////////////////////////////////////////////////////////////
			//
			//            World Coordinate assignment methods
			// 
			////////////////////////////////////////////////////////////
			// NOTE: These are used if the child class does not provide their own.

			/// <summary>
			/// Sets the vector position of the camera.
			/// </summary>
			inline virtual void SetPosition(float x, float y, float z) override
			{
				m_position = Vector3(x, y, z);
			}

			inline virtual void SetPosition(const Vector3& vector) override
			{
				m_position = vector;
			}

			inline virtual void SetPosition(Vector3&& vector) override
			{
				m_position = std::move(vector);
			}

			/// <summary>
			/// Sets the orientation of the object in the world.
			/// </summary>
			inline virtual void SetOrientation(float x, float y, float z) override
			{
				m_orientation = Vector3(x, y, z);
			}

			inline virtual void SetOrientation(const Vector3& vector) override
			{
				m_orientation = vector;
			}

			inline virtual void SetOrientation(Vector3&& vector) override
			{
				m_orientation = std::move(vector);
			}

			////////////////////////////////////////////////////////////
			//
			//            Camera Orientation assignment methods
			// 
			////////////////////////////////////////////////////////////

			/// <summary>
			/// Sets the lookat vector of the camera.
			/// </summary>
			inline virtual void SetLookAt(float x, float y, float z) override
			{
				m_lookAt = Vector3(x, y, z);
			}

			inline virtual void SetLookAt(const Vector3& vector) override
			{
				m_lookAt = vector;
			}

			inline virtual void SetLookAt(Vector3&& vector) override
			{
				m_lookAt = std::move(vector);
			}

			/// <summary>
			/// Sets the lookat vector of the camera.
			/// </summary>
			inline virtual void SetUp(float x, float y, float z) override
			{
				m_up = Vector3(x, y, z);
			}

			inline virtual void SetUp(const Vector3& vector) override
			{
				m_up = vector;
			}

			inline virtual void SetUp(Vector3&& vector) override
			{
				m_up = std::move(vector);
			}

			////////////////////////////////////////////////////////////
			//
			//                Movement methods
			// 
			////////////////////////////////////////////////////////////

			inline virtual void Yaw(float value) override
			{
				m_yaw = value;
			}

			inline virtual void Pitch(float value) override
			{
				m_pitch = value;
			}

			inline virtual void Roll(float value) override
			{
				m_roll = value;
			}

			inline virtual void Forward(float value) override
			{
				m_forward = value;
			}

		protected:

			////////////////////////////////////////////////////////////
			//
			//                Member Vars
			// 
			////////////////////////////////////////////////////////////

			float m_yaw = 0.0f, m_pitch = 0.0f, m_roll = 0.0f;
			float m_strafe = 0.0f, m_forward = 0.0f;

			Vector3 m_lookAt = Vector3(0.0f, 0.0f, 1.0f);
			Vector3 m_up = Vector3(0.0f, 1.0f, 0.0f);

			//Object coordinates.
			Vector3 m_position = Vector3();
			Vector3 m_orientation = Vector3();
		};
	};
};

#endif
