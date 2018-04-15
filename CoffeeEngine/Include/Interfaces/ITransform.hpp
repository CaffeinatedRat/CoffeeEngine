//--------------------------------------------------------------------------------------
// Description: The transform interface allows an object to be transformed geometrically.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _ITRANSFORM_INTERFACE_H_
#define _ITRANSFORM_INTERFACE_H_

#pragma once

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
			virtual void Rotate(float x, float y, float z) = 0;

			/// <summary>
			/// Translate the object among one or more of the 3-axises.
			/// </summary>
			virtual void Translate(float x, float y, float z) = 0;

			/// <summary>
			/// Scale the object among one or more of the 3-axises.
			/// </summary>
			virtual void Scale(float x, float y, float z) = 0;
		};
	};
};

#endif
