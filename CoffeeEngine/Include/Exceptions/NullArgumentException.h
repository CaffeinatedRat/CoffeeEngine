//--------------------------------------------------------------------------------------
// Description: This exception usually occurs if an argument that is supplied is null.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _NULLARGUMENT_EXCEPTION_H_
#define _NULLARGUMENT_EXCEPTION_H_

#include <iostream>
#include "stdarg.h"

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class NullArgumentException : public Exception
		{
		public:
		
			NullArgumentException()
			{
				m_sMessage = "An argument is null.";
			}

			NullArgumentException(std::string sMessage) : Exception(sMessage) {}
			
			NullArgumentException(int nAmount, ...)
			{
				va_list vl;
				va_start(vl, nAmount);

				std::string sCompiledMessage = "";

				for(int i = 0; i < nAmount; i++)
				{
					std::string msg = std::string(va_arg(vl, const char*));
					sCompiledMessage.append(msg);
				}

				va_end(vl);

				m_sMessage = sCompiledMessage;
			}

			NullArgumentException(const NullArgumentException& exception) : Exception(exception) {}
		};
	};
};

#endif