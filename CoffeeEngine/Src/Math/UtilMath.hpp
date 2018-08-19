//--------------------------------------------------------------------------------------
// Description: Utility math functions.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _UTIL_MATH_H_
#define _UTIL_MATH_H_

#pragma once

namespace CoffeeEngine
{
	namespace Math
	{
		namespace Trig
		{
			const float C_PI = 3.14159265f;
			const float C_2PI = C_PI * 2.0f;
			const float C_HalfPI = C_PI / 2.0f;
			const float C_QuarterPI = C_PI / 4.0f;

			constexpr inline float DegsToRadsf(float value) { return value * C_PI / 180; }
			constexpr inline float RadsToDegsf(float value) { return value * 180 / C_PI; }
		};

		inline uint8_t PrecomputeLog2Byte(uint16_t value)
		{
			switch (value)
			{
			case 1:
				return 0U;
			case 2:
				return 1U;
			case 4:
				return 2U;
			case 8:
				return 3U;
			case 16:
				return 4U;
			case 32:
				return 5U;
			case 64:
				return 6U;
			case 128:
				return 7U;
			case 256:
				return 8U;
			default:
				return 0U;
			}
		};
	}
}

#endif
