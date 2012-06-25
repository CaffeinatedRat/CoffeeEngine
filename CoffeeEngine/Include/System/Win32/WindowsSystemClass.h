//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _WINDOWS_SYSTEM_CLASS_H_
#define _WINDOWS_SYSTEM_CLASS_H_

#include "stdafx.h"
#include "Common.h"
#include "Interfaces\ISystem.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Engine\CoffeeEngineClass.h"
#include "Utility\Logger.h"

#define MAX_LOADSTRING 100

using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Engine;
using namespace CoffeeEngine::Utility;

namespace CoffeeEngine
{
	namespace System
	{
		class WindowsSystemClass : public ISystem
		{
		private:

			//Windows specific member variables
			HINSTANCE m_hInstance;
			HWND m_hWnd;
			TCHAR m_szTitle[MAX_LOADSTRING];
			TCHAR m_szWindowClass[MAX_LOADSTRING];

			int m_nScreenWidth, m_nScreenHeight;

			bool m_bIsIdle;
			BaseGraphicsClass* m_pGraphics;
			CoffeeEngineClass* m_pCoffeeEngine;

			std::vector<std::wstring> m_log;

		public:
		
			WindowsSystemClass();
			WindowsSystemClass(const WindowsSystemClass&);
			~WindowsSystemClass();

			/// <summary>
			/// Attempts to initialize the operating system object, as well as all internal systems such as the graphics engine and main game engine.
			/// </summary>
			bool Initialize();

			/// <summary>
			/// Begins running the operating system object once the system has been successfully initialized.
			/// </summary>
			void Run();
		
			/// <summary>
			/// Performs an individual frame render.
			/// </summary>		
			bool Frame();

			/// <summary>
			/// Begins the process of shutting down the operating system class and all dependencies.
			/// </summary>
			void Shutdown();

			/// <summary>
			/// Writes a message to the OSes console.
			/// </summary>
			void ConsoleWrite(std::string sMessage);

			/// <summary>
			/// Returns the root directory the executable is running in.
			/// </summary>
			std::string GetCurrentDirectory();

			////////////////////////////////////////////////////////////
			//
			//                Windows Specific methods
			// 
			////////////////////////////////////////////////////////////

			LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
			
			/// <summary>
			/// Returns the windows handle.
			/// </summary>
			inline HWND GetHWND() { return m_hWnd; }

		protected:

			/// <summary>
			/// Initializes and creates the window for the Windows Operating System.
			/// </summary>
			bool InitializeWindow();
		};
	};
};

#endif