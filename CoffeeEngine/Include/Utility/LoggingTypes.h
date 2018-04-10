//--------------------------------------------------------------------------------------
// Description: Logging types.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _LOGGER_UTILITY_TYPES_H_
#define _LOGGER_UTILITY_TYPES_H_

#pragma once

#include "Common.h"
#include "UtilMath.h"
#include <type_traits>

namespace CoffeeEngine
{
	namespace Utility
	{
		namespace Logging
		{
			////////////////////////////////////////////////////////////
			// Scoped Datatypes
			////////////////////////////////////////////////////////////

			/// <summary>
			/// An enumeration for the various types of logging that is used to set the verbosity or the event type.
			/// </summary>
			enum class LogLevelType : unsigned
			{
				None = 0,
				Critical = 1,
				Error = 2,
				Warning = 4,
				Informational = 8,
				Diagnostic = 16
			};

			/// <summary>
			/// Returns the name of the LogLevelType enumeration.
			/// </summary>
			inline const char* GetLogLevelName(const LogLevelType logLevelType) {

				const char* LogLevelTypeNames[] = {
					"Critical",
					"Error",
					"Warning",
					"Informational",
					"Diagnostic"
				};

				auto logLevelIntegral = PrecomputeLog2Byte(static_cast<uint16_t>(logLevelType));
				return (logLevelIntegral < std::size(LogLevelTypeNames)) ? LogLevelTypeNames[logLevelIntegral] : "Undefined";
			}

			inline LogLevelType operator|(LogLevelType lhs, LogLevelType rhs)
			{
				return static_cast<LogLevelType>(std::underlying_type<LogLevelType>::type(lhs) | std::underlying_type<LogLevelType>::type(rhs));
			};

			inline LogLevelType operator&(LogLevelType lhs, LogLevelType rhs)
			{
				return static_cast<LogLevelType>(std::underlying_type<LogLevelType>::type(lhs) & std::underlying_type<LogLevelType>::type(rhs));
			};

			inline LogLevelType operator|=(LogLevelType lhs, LogLevelType rhs)
			{
				return lhs = static_cast<LogLevelType>(std::underlying_type<LogLevelType>::type(lhs) | std::underlying_type<LogLevelType>::type(rhs));
			};

			inline LogLevelType operator&=(LogLevelType lhs, LogLevelType rhs)
			{
				return lhs = static_cast<LogLevelType>(std::underlying_type<LogLevelType>::type(lhs) & std::underlying_type<LogLevelType>::type(rhs));
			};

			namespace Verbosity {
				////////////////////////////////////////////////////////////
				// Scoped Datatypes
				////////////////////////////////////////////////////////////
				const LogLevelType Detailed = LogLevelType::Critical | LogLevelType::Error | LogLevelType::Warning | LogLevelType::Informational | LogLevelType::Diagnostic;
				const LogLevelType Normal = LogLevelType::Critical | LogLevelType::Error | LogLevelType::Warning | LogLevelType::Informational;
				const LogLevelType Minimum = LogLevelType::Critical | LogLevelType::Error | LogLevelType::Warning;
				const LogLevelType Error = LogLevelType::Critical | LogLevelType::Error;
			};
		};
	};
};

#endif