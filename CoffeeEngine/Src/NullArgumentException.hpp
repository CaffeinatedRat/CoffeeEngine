//--------------------------------------------------------------------------------------
// Description: This exception usually occurs if an argument that is supplied is null.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _NULLARGUMENT_EXCEPTION_H_
#define _NULLARGUMENT_EXCEPTION_H_

#pragma once

#include "Exception.hpp"

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NullArgumentException : public Exception
		{
		public:
		
			NullArgumentException(const std::string& className, const std::string& methodName, const std::string& argument)
				: Exception(className, methodName)
			{
				m_Message.append("The argument ");
				m_Message.append(argument);
				m_Message.append(" is null.");
			}
			
			NullArgumentException(const NullArgumentException& exception) : Exception(exception) {}
		};
	};
};

#endif
