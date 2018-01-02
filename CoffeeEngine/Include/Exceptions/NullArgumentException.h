//--------------------------------------------------------------------------------------
// Description: This exception usually occurs if an argument that is supplied is null.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _NULLARGUMENT_EXCEPTION_H_
#define _NULLARGUMENT_EXCEPTION_H_

#pragma once

#include "Exceptions/Exception.h"

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NullArgumentException : public Exception
		{
		public:
		
			NullArgumentException(const std::string& sClassName, const std::string& sMethodName, const std::string& sArgument)
				: Exception(sClassName, sMethodName)
			{
				m_sMessage.append("The argument ");
				m_sMessage.append(sArgument);
				m_sMessage.append(" is null.");
			}
			
			NullArgumentException(const NullArgumentException& exception) : Exception(exception) {}
		};
	};
};

#endif