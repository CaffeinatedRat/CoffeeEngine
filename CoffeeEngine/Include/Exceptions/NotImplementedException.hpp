//--------------------------------------------------------------------------------------
// Description: Provides a not implemented exception for features that have not been built yet.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _NOT_IMPLEMENTED_EXCEPTION_EXCEPTION_H_
#define _NOT_IMPLEMENTED_EXCEPTION_EXCEPTION_H_

#pragma once

#include "Exceptions/Exception.h"

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NotImplementedException: public Exception
		{
		public:
		
			NotImplementedException(const std::string& sClassName, const std::string& sMethodName)
				: Exception(sClassName, sMethodName)
			{
				m_sMessage = "This method is not implemented.";
			}

			NotImplementedException(const NotImplementedException& exception) : Exception(exception) {}
		};
	};
};

#endif
