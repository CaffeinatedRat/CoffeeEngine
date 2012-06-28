//--------------------------------------------------------------------------------------
// Description: This exception usually occurs if an argument that is supplied is null.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _NULLARGUMENT_EXCEPTION_H_
#define _NULLARGUMENT_EXCEPTION_H_

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NullArgumentException : public Exception
		{
		public:
		
			NullArgumentException(std::string sClassName, std::string sMethodName, std::string sArgument)
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