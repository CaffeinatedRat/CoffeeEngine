//--------------------------------------------------------------------------------------
// Description: The object interface allows an objects to have common methods in the world.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _IOBJECT_INTERFACE_H_
#define _IOBJECT_INTERFACE_H_

#pragma once

#include "Math/Vectors.hpp"

using namespace CoffeeEngine::Math;

namespace CoffeeEngine
{
	namespace Engine
	{
		class IObject
		{
		public:

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
		};
	};
};

#endif
