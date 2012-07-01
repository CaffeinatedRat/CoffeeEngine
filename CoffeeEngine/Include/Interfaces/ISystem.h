//--------------------------------------------------------------------------------------
// Description: The operating system interface.  Used to provide a light-weight skeleton of how the other operating system classes should be created.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _ISYSTEM_INTERFACE_H_
#define _ISYSTEM_INTERFACE_H_

#include <iostream>
#include "Interfaces\ITimer.h"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class ISystem
		{
		public:
		
			/// <summary>
			/// Attempts to initialize the operating system object, as well as all internal systems such as the graphics engine and main game engine.
			/// </summary>
			virtual bool Initialize() = 0;
			
			/// <summary>
			/// Begins running the operating system object once the system has been successfully initialized.
			/// </summary>
			virtual void Run() = 0;

			/// <summary>
			/// Begins the process of shutting down the operating system class and all dependencies.
			/// </summary>
			virtual void Shutdown() = 0;

			/// <summary>
			/// Writes a message to the OSes console.
			/// </summary>
			virtual void ConsoleWrite(std::string sMessage) = 0;

			/// <summary>
			/// Returns the root directory the executable is running in.
			/// </summary>
			virtual std::string GetCurrentApplicationDirectory() = 0;

			/// <summary>
			/// Create's system timer.
			/// NOTE: This creates a new instance of the object.  It is your responsibility to delete this instance when done with it.
			/// </summary>
			virtual ITimer* CreateTimer() = 0;
		};
	};
};

#endif