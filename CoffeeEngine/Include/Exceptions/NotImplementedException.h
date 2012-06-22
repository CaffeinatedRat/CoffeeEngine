//--------------------------------------------------------------------------------------
// Description: Provides a not implemented exception for features that have not been built yet.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _NOT_IMPLEMENTED_EXCEPTION_EXCEPTION_H_
#define _NOT_IMPLEMENTED_EXCEPTION_EXCEPTION_H_

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NotImplementedException: public Exception
		{
		public:
		
			NotImplementedException(std::string sClassName, std::string sMethodName)
				: Exception(sClassName, sMethodName)
			{
				m_sMessage = "This method is not implemented.";
			}

			NotImplementedException(const NotImplementedException& exception) : Exception(exception) {}
		};
	};
};

#endif