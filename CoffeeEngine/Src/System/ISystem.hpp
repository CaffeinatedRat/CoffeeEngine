//--------------------------------------------------------------------------------------
// Description: The operating system interface.
// Used to provide a light-weight skeleton of how the other operating system classes should be created.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _ISYSTEM_INTERFACE_H_
#define _ISYSTEM_INTERFACE_H_

#pragma once

#include "Common.hpp"
#include "Utility/Logger.hpp"
#include "ITimer.hpp"
#include "ISystemListener.hpp"
#include "Input/Keyboard.hpp"

using namespace CoffeeEngine::Input;
 
namespace CoffeeEngine
{
	namespace Interfaces
	{
		class ISystem
		{
		public:

			ISystem() = default;
			//NOTE: Very important, otherwise if we don't add a virtual destructor all of our inherited classes will never have their destructor invoked.
			virtual ~ISystem() = default;
		
			/// <summary>
			/// Attempts to initialize the operating system object, as well as all internal systems such as the graphics engine and main game engine.
			/// </summary>
			virtual bool Initialize(ISystemListener* listener) = 0;
			
			/// <summary>
			/// Begins running the operating system object once the system has been successfully initialized.
			/// </summary>
			virtual void Run() = 0;

			/// <summary>
			/// Begins the process of shutting down the operating system class and all dependencies.
			/// </summary>
			virtual void Shutdown() = 0;

			/// <summary>
			/// Writes to the event log.
			/// </summary>
			virtual void WriteToLog(char const*, Utility::Logging::LogLevelType = Utility::Logging::LogLevelType::Informational) noexcept = 0;
			virtual void WriteToLog(const std::string&, Utility::Logging::LogLevelType=Utility::Logging::LogLevelType::Informational) noexcept = 0;
			virtual void WriteToLog(const std::stringstream&, Utility::Logging::LogLevelType=Utility::Logging::LogLevelType::Informational) noexcept = 0;
			virtual void WriteToLog(Exception&) noexcept = 0;			

			/// <summary>
			/// Returns the root directory the executable is running in.
			/// </summary>
			virtual std::string GetCurrentApplicationDirectory() const = 0;

			/// <summary>
			/// Create's system timer.
			/// NOTE: This creates a new instance of the object.  It is your responsibility to delete this instance when done with it.
			/// </summary>
			virtual ITimer* CreateTimer() = 0;
		};
	};
};

#endif
