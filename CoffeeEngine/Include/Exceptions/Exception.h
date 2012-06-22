//--------------------------------------------------------------------------------------
// Description: Provides a light-weight base exception.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _EXCEPTION_EXCEPTION_H_
#define _EXCEPTION_EXCEPTION_H_

#include "Common.h"
#include <sstream>

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
				m_sClassName = "Undefined";
				m_sMethodName = "Undefined";
			}

			Exception(std::string sClassName, std::string sMethodName)
			{
				m_sMessage = "An undefined exception has occured.";
				m_sClassName = sClassName;
				m_sMethodName = sMethodName;
			}

			Exception(std::string sClassName, std::string sMethodName, std::string sMessage)
			{
				m_sMessage = sMessage;
				m_sClassName = sClassName;
				m_sMethodName = sMethodName;
			}

			Exception(const Exception& exception)
			{
				m_sMessage = exception.m_sMessage;
				m_sClassName = exception.m_sClassName;
				m_sMethodName = exception.m_sMethodName;
			}

			virtual std::string GetMessage() { return m_sMessage; }
			virtual std::string GetClass() { return m_sClassName; }
			virtual std::string GetMethod() { return m_sMethodName; }
			virtual std::string ToString()
			{
				std::stringstream ss;
				ss << "[" << m_sClassName << ":" << m_sMethodName << "] " << m_sMessage;
				return ss.str();
			}

		protected:
			std::string m_sMessage;
			std::string m_sClassName;
			std::string m_sMethodName;
		};
	};
};

#endif