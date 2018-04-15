//--------------------------------------------------------------------------------------
// Description: Provides a light-weight base exception.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _EXCEPTION_EXCEPTION_H_
#define _EXCEPTION_EXCEPTION_H_

#pragma once

#include <sstream>

namespace CoffeeEngine
{
	namespace Exceptions
	{
		class Exception
		{
		public:
		
			Exception() = default;

			Exception(const std::string& sClassName, const std::string& sMethodName) 
				: m_sClassName(sClassName), m_sMethodName(sMethodName) {}

			Exception(const std::string& sClassName, const std::string& sMethodName, const std::string& sMessage)
				: Exception(sClassName, sMethodName) { m_sMessage = sMessage; }

			Exception(const Exception& exception)
			{
				m_sMessage = exception.m_sMessage;
				m_sClassName = exception.m_sClassName;
				m_sMethodName = exception.m_sMethodName;
			}

			virtual std::string GetMessage() const noexcept { return m_sMessage; }
			virtual std::string GetClass() const noexcept { return m_sClassName; }
			virtual std::string GetMethod() const noexcept { return m_sMethodName; }
			virtual std::string ToString() noexcept
			{
				std::stringstream ss;
				ss << "[" << m_sClassName << "::" << m_sMethodName << "] " << m_sMessage;
				return ss.str();
			}

		protected:
			std::string m_sMessage = "An undefined exception has occured.";
			std::string m_sClassName = "Undefined";
			std::string m_sMethodName = "Undefined";
		};
	};
};

#endif
