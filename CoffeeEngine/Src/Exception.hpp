//--------------------------------------------------------------------------------------
// Description: Provides a light-weight base exception.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
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

			Exception(const std::string& className, const std::string& methodName) 
				: m_ClassName(className), m_MethodName(methodName) {}

			Exception(const std::string& className, const std::string& methodName, const std::string& message)
				: Exception(className, methodName)
			{
				m_Message = message;
			}

			Exception(const Exception& exception)
			{
				m_Message = exception.m_Message;
				m_ClassName = exception.m_ClassName;
				m_MethodName = exception.m_MethodName;
			}

			virtual std::string GetMessage() const noexcept { return m_Message; }
			virtual std::string GetClass() const noexcept { return m_ClassName; }
			virtual std::string GetMethod() const noexcept { return m_MethodName; }
			virtual std::string ToString() noexcept
			{
				std::stringstream ss;
				ss << "[" << m_ClassName << "::" << m_MethodName << "] " << m_Message;
				return ss.str();
			}

		protected:
			std::string m_Message = "An undefined exception has occured.";
			std::string m_ClassName = "Undefined";
			std::string m_MethodName = "Undefined";
		};
	};
};

#endif
