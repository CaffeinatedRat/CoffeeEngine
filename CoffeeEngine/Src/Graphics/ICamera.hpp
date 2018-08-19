//--------------------------------------------------------------------------------------
// Description: The camera interface.  Used to provide a light-weight skeleton for the camera.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _ICAMERA_INTERFACE_H_
#define _ICAMERA_INTERFACE_H_

#include "Math/Vectors.hpp"
#include "Engine/IObject.hpp"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		using namespace CoffeeEngine::Engine;
		using namespace CoffeeEngine::Math;

		class ICamera : public IObject
		{
		public:
		
			/// <summary>
			/// Attempts to initialize the model object.
			/// </summary>
			virtual bool Initialize() = 0;

			/// <summary>
			/// Begin rendering the camera.
			/// </summary>
			virtual void Render(float) = 0;

			/// <summary>
			/// Begins the process of cleaning up the model.
			/// </summary>
			virtual void Shutdown() = 0;

			/// <summary>
			/// Updates the graphics properties such as aspect ratio and fov.
			/// </summary>
			virtual void UpdateGraphicsProperties() = 0;

			/// <summary>
			/// Sets the position of the object in the world.
			/// </summary>
			virtual void SetPosition(float, float, float) = 0;
			virtual void SetPosition(const Vector3&) = 0;
			virtual void SetPosition(Vector3&&) = 0;

			/// <summary>
			/// Sets the orientation of the object in the world.
			/// </summary>
			virtual void SetOrientation(float, float, float) = 0;
			virtual void SetOrientation(const Vector3&) = 0;
			virtual void SetOrientation(Vector3&&) = 0;

			/// <summary>
			/// Sets the lookat vector of the camera.
			/// </summary>
			virtual void SetLookAt(float, float, float) = 0;
			virtual void SetLookAt(const Vector3&) = 0;
			virtual void SetLookAt(Vector3&&) = 0;

			/// <summary>
			/// Sets the up vector of the camera.
			/// </summary>
			virtual void SetUp(float, float, float) = 0;
			virtual void SetUp(const Vector3&) = 0;
			virtual void SetUp(Vector3&&) = 0;

			////////////////////////////////////////////////////////////
			//
			//                Movement methods
			// 
			////////////////////////////////////////////////////////////
			virtual void Yaw(float) = 0;
			virtual void Pitch(float) = 0;
			virtual void Roll(float) = 0;
			virtual void Forward(float) = 0;
			virtual void Strafe(float) = 0;
		};
	};
};

#endif
