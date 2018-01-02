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
		inline unsigned int PrecomputeLog2Byte(unsigned int value)
		{
			switch (value)
			{
			case 1:
				return 0;
			case 2:
				return 1;
			case 4:
				return 2;
			case 8:
				return 3;
			case 16:
				return 4;
			case 32:
				return 5;
			case 64:
				return 6;
			case 128:
				return 7;
			case 256:
				return 8;
			default:
				return 0;
			}
		};
	}
}

#endif