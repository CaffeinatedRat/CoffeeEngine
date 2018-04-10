//--------------------------------------------------------------------------------------
// Description: Utility math functions.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _UTIL_MATH_H_
#define _UTIL_MATH_H_

#pragma once

namespace CoffeeEngine
{
	namespace Utility
	{
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