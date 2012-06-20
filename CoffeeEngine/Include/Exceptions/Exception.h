//--------------------------------------------------------------------------------------
// Description: Provides a light-weight base exception.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _EXCEPTION_EXCEPTION_H_
#define _EXCEPTION_EXCEPTION_H_

#include <iostream>

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class Exception
		{
		public:
		
			Exception()
			{
				m_sMessage = "An undefined exception has occured.";
			}

			Exception(std::string sMessage)
			{
				m_sMessage = sMessage;
			}

			Exception(const Exception& exception)
			{
				m_sMessage = exception.m_sMessage;
			}

			virtual std::string GetMessage() { return m_sMessage; }

		protected:
			std::string m_sMessage;
		};
	};
};

#endif