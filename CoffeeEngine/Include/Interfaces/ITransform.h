//--------------------------------------------------------------------------------------
// Description: The transform interface allows an object to be transformed geometrically.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _ITRANSFORM_INTERFACE_H_
#define _ITRANSFORM_INTERFACE_H_

#include "Common.h"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class ITransform
		{
		public:
		
			/// <summary>
			/// Rotate the object among one or more of the 3-axises.
			/// </summary>
			virtual void Rotate(float x, float y, float z);

			/// <summary>
			/// Translate the object among one or more of the 3-axises.
			/// </summary>
			virtual void Translate(float x, float y, float z);

			/// <summary>
			/// Scale the object among one or more of the 3-axises.
			/// </summary>
			virtual void Scale(float x, float y, float z);
		};
	};
};

#endif