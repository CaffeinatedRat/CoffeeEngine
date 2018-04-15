//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#ifndef _WINDOWS_SYSTEM_CLASS_H_
#define _WINDOWS_SYSTEM_CLASS_H_

#pragma once

#include "stdafx.h"
#include "Common.h"
#include <memory>

#include "Utility/Logger.h"
#include "Interfaces/ISystem.h"
#include "Interfaces/ISystemListener.h"
#include "Interfaces/ITimer.h"

#define MAX_LOADSTRING 100

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace System
	{
		enum class WindowsOSState
		{
			UNKNOWN,
			INITIALIZED,
			SHUTDOWN
		};

		class WindowsSystemClass : public ISystem
		{
			using LogLevelType = CoffeeEngine::Utility::Logging::LogLevelType;
			using Logger = CoffeeEngine::Utility::Logging::Logger;

		public:

			WindowsSystemClass() = default;
			WindowsSystemClass(Logger *pLogger);
			WindowsSystemClass(const WindowsSystemClass&);
			virtual ~WindowsSystemClass() noexcept override;

			/// <summary>
			/// Attempts to initialize the operating system object with a provided listener.
			/// </summary>
			bool Initialize(ISystemListener* listener) override;

			/// <summary>
			/// Begins running the operating system object once the system has been successfully initialized.
			/// </summary>
			void Run() override;

			/// <summary>
			/// Begins the process of shutting down the operating system class and all dependencies.
			/// </summary>
			void Shutdown() override;

			/// <summary>
			/// Writes to the event log.
			/// </summary>
			void WriteToLog(const std::string&, LogLevelType = LogLevelType::Informational) noexcept override;
			void WriteToLog(const char*, LogLevelType = LogLevelType::Informational) noexcept override;
			void WriteToLog(Exception&) noexcept override;

			/// <summary>
			/// Returns the root directory the executable is running in.
			/// </summary>
			std::string GetCurrentApplicationDirectory() const;

			/// <summary>
			/// Create's system timer.
			/// NOTE: This creates a new instance of the object.  It is your responsibility to delete this instance when done with it.
			/// </summary>
			inline ITimer* CreateTimer() override;

			////////////////////////////////////////////////////////////
			//
			//                Windows Specific methods
			// 
			////////////////////////////////////////////////////////////

			LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

			/// <summary>
			/// Returns the windows handle.
			/// </summary>
			inline const HWND& GetHWND() const { return m_hWnd; }

			/// <summary>
			/// Returns the windows instance handle..
			/// </summary>
			inline const HINSTANCE& GetHInstance() const { return m_hInstance; }

		protected:

			/// <summary>
			/// Initializes and creates the window for the Windows Operating System.
			/// </summary>
			bool InitializeWindow();

			/// <summary>
			/// Returns an error message for the last windows error.
			/// </summary>
			std::string GetLastErrorMessage() const;

		private:
			/// <summary>
			/// Registers the core windows class.
			/// </summary>
			void RegisterWindowsClass(HINSTANCE hInstance);

		private:

			//Windows specific member variables
			HINSTANCE m_hInstance = nullptr;
			HWND m_hWnd = nullptr;

			//Windows specific strings.
			TCHAR m_szTitle[MAX_LOADSTRING];
			TCHAR m_szWindowClass[MAX_LOADSTRING];

			//Internal system variables.
			int m_nScreenWidth = 0, m_nScreenHeight = 0;
			bool m_bIdleInBackground = false;
			//bool m_bClassRegistered = false;

			//Internal states
			//We are active by default.
			bool m_bIsActive = false;

			//We are not idling.
			bool m_bIsIdiling = false;

			WindowsOSState m_bCurrentState = WindowsOSState::UNKNOWN;

			//Allows the Shutdown method to be idempotent.
			//bool m_bHasShutdown = false;

			ISystemListener *m_pListener = nullptr;
			Logger* m_plogger = nullptr;
		};
	};
};

#endif

#endif