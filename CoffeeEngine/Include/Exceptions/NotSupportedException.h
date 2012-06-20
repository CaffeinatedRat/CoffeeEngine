//--------------------------------------------------------------------------------------
// Description: Provides a not supported exception for features that have not been built yet.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _NOT_SUPPORTED_EXCEPTION_EXCEPTION_H_
#define _NOT_SUPPORTED_EXCEPTION_EXCEPTION_H_

#include <iostream>
#include <ios>

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NotSupportedException: public Exception
		{
		public:
		
			NotSupportedException(std::string sMethodName)
			{
				m_sMessage = "The method ";
				m_sMessage.append(sMethodName);
				m_sMessage.append(" is not supported.");
			}

			NotSupportedException(const NotSupportedException& exception) : Exception(exception) {}
		};
	};
};

#endif