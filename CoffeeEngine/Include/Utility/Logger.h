//--------------------------------------------------------------------------------------
// Description: A logging utility.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _LOGGER_UTILITY_CLASS_H_
#define _LOGGER_UTILITY_CLASS_H_

#include "Common.h"

namespace CoffeeEngine
{
	namespace Utility
	{
		class Logger
		{
		public:
			static const char* LOG_FILE_NAME;

		public:
		
			Logger();
			~Logger();

			/// <summary>
			/// Writes an timestamped event to the error log.
			/// </summary>
			static void Write(std::string sEvent);
		};
	};
};

#endif