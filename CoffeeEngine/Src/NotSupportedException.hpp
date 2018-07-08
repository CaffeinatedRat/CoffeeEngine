//--------------------------------------------------------------------------------------
// Description: Provides a not supported exception for features that are not supported.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _NOT_SUPPORTED_EXCEPTION_EXCEPTION_H_
#define _NOT_SUPPORTED_EXCEPTION_EXCEPTION_H_

#pragma once

#include "Exception.hpp"

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NotSupportedException : public Exception
		{
		public:

			NotSupportedException(const std::string& className, const std::string& methodName)
				: Exception(className, methodName)
			{
				m_Message = "This type is not supported.";
			}

			NotSupportedException(const NotSupportedException& exception) : Exception(exception) {}
		};
	};
};

#endif
