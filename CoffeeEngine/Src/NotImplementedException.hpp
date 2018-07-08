//--------------------------------------------------------------------------------------
// Description: Provides a not implemented exception for features that have not been built yet.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _NOT_IMPLEMENTED_EXCEPTION_EXCEPTION_H_
#define _NOT_IMPLEMENTED_EXCEPTION_EXCEPTION_H_

#pragma once

#include "Exception.hpp"

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NotImplementedException: public Exception
		{
		public:
		
			NotImplementedException(const std::string& className, const std::string& methodName)
				: Exception(className, methodName)
			{
				m_Message = "This method is not implemented.";
			}

			NotImplementedException(const NotImplementedException& exception) : Exception(exception) {}
		};
	};
};

#endif
