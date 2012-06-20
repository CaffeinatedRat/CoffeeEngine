//--------------------------------------------------------------------------------------
// Description: The camera interface.  Used to provide a light-weight skeleton for the camera.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _ICAMERA_INTERFACE_H_
#define _ICAMERA_INTERFACE_H_

#include "Common.h"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class ICamera
		{
		public:
		
			/// <summary>
			/// Attempts to initialize the model object.
			/// </summary>
			virtual bool Initialize() = 0;

			/// <summary>
			/// Begins the process of cleaning up the model.
			/// </summary>
			virtual void Shutdown() = 0;

			/// <summary>
			/// Begin rendering the camera.
			/// </summary>
			virtual void Render() = 0;
		};
	};
};

#endif