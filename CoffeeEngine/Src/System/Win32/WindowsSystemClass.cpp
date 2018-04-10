//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

//Windows specific.
#include "../Resources/Resource.h"

#include "Common.h"
#include "Utility/Logger.h"

#include "System/Win32/Windows_EntryPoint.h"
#include "System/Win32/WindowsSystemClass.h"
#include "System/Win32/TimerClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Utility;
using namespace CoffeeEngine::Utility::Logging;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

WindowsSystemClass::WindowsSystemClass(const WindowsSystemClass& systemClass)
{
	m_hInstance = systemClass.m_hInstance;
	m_hWnd = systemClass.m_hWnd;
	m_bIsActive = systemClass.m_bIsActive;
	m_bIsIdiling = systemClass.m_bIsIdiling;
}

WindowsSystemClass::WindowsSystemClass(Logger *pLogger)
{
	if (pLogger == nullptr)
		throw NullArgumentException("WindowsSystemClass", "Constructor", "pLogger");

	m_plogger = pLogger;
}

WindowsSystemClass::~WindowsSystemClass()
{
	Shutdown();
}


////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool WindowsSystemClass::Initialize(ISystemListener* listener)
{
	if (listener == nullptr)
	{
		//Add the heavy action of an exception but increase diag when necessary.
		throw NullArgumentException("WindowsSystemClass", "Initialize", "listener");
	}

	//Assign the listener.
	//Technically we could make this an array of multiple listeners if necessary.
	m_pListener = listener;

	WriteToLog("[WindowsSystemClass::Initialize] Initializing...", LogLevelType::Informational);

	if (InitializeWindow())
		return true;

	WriteToLog("[WindowsSystemClass::Initialize] Initializing failed!", LogLevelType::Error);

	return false;
}

void WindowsSystemClass::Run()
{
	WriteToLog("[WindowsSystemClass::Run] Beginning the message pump.", LogLevelType::Informational);

	//Begin the windows message pump.
	MSG msg;
	HACCEL hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_COFFEEENGINE));

	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		//Windows messages have the highest priority.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message != WM_QUIT)
			{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		//The engine is invoked while the application is idling.
		else
		{
			if (m_pListener != nullptr)
			{
				m_pListener->OnIdle(m_bIsActive);
			}
			else
			{
				//Sleep for a bit to prevent pegging the CPU.
				//This occurs when the application is in the background.
				Sleep(200);
			}
		}
	}

	WriteToLog("[WindowsSystemClass::Run] Ending the message pump.", LogLevelType::Informational);
}

/// <summary>
/// Begins the process of shutting down the OS handler and cleaning up any remaining resources.
/// </summary>
void WindowsSystemClass::Shutdown()
{
	assert(m_bCurrentState != WindowsOSState::SHUTDOWN);

	//This flag allows this method to be idempotent.
	if (m_bCurrentState != WindowsOSState::SHUTDOWN)
	{
		WriteToLog("[WindowsSystemClass::Shutdown] Shutting down...", LogLevelType::Informational);

		//Clean up the window.
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;

		UnregisterClass(m_szWindowClass, m_hInstance);

		m_bCurrentState = WindowsOSState::SHUTDOWN;
	}
}

////////////////////////////////////////////////////////////
//
//                Utility Methods
// 
////////////////////////////////////////////////////////////

/// <summary>
/// Writes a const character string as an error event to the log.
/// </summary>
/// <param name="szEvent">Event to write to the log.</param>
void WindowsSystemClass::WriteToLog(const char* szEvent, LogLevelType logEventType) noexcept
{
	if (m_plogger != nullptr)
		m_plogger->Write(szEvent, logEventType);
}

/// <summary>
/// Writes an event to the event log.
/// </summary>
/// <param name="sEvent">Event to write to the log.</param>
/// <param name="logEventType">Type of log event.</param>
void WindowsSystemClass::WriteToLog(const std::string& sEvent, LogLevelType logEventType) noexcept
{
	if (m_plogger != nullptr)
		m_plogger->Write(sEvent, logEventType);
}

/// <summary>
/// Writes an exception as an error event to the log.
/// </summary>
/// <param name="exception">Exception to write to the log as an error.</param>
void WindowsSystemClass::WriteToLog(Exception& exception) noexcept
{
	WriteToLog(exception.ToString(), LogLevelType::Error);
}

std::string WindowsSystemClass::GetCurrentApplicationDirectory() const
{
	std::string sRootDirectory = "";
	wchar_t* buffer = nullptr;
	char* convertedString = nullptr;

	try
	{
		//Calculate the need size of the buffer.
		DWORD dwBufferSize = ::GetCurrentDirectory(0, nullptr);

		//Allocate memory for the wide character string and return an empty string if no memory could be allocated.
		if ((buffer = new wchar_t[dwBufferSize]) != nullptr)
		{
			//Get the current directory.
			//NOTE: This will be returned as a wide character string.
			DWORD dwStatus = ::GetCurrentDirectory(dwBufferSize, buffer);
			if (dwStatus > 0)
			{
				//Attempt to convert the wide character string to a single character string.
				size_t bufferSize = wcslen(buffer) + 1;
				if ((convertedString = new char[bufferSize]) != nullptr)
				{
					size_t convertedChars = 0;
					wcstombs_s(&convertedChars, convertedString, bufferSize, buffer, _TRUNCATE);
					sRootDirectory = std::string(convertedString);
				}
				//END OF if ( (convertedString = new char[bufferSize]) != nullptr)..
			}
			//END OF if(dwStatus > 0)...
		}
		//END OF if ( (buffer = new wchar_t[dwBufferSize]) != nullptr)...
	}
	catch (...) {}

	SAFE_DELETE(buffer);
	SAFE_DELETE(convertedString);

	return sRootDirectory;
}

inline ITimer* WindowsSystemClass::CreateTimer()
{
	return ((ITimer*)new TimerClass());
}

////////////////////////////////////////////////////////////
//
//                Protected Methods
// 
////////////////////////////////////////////////////////////

bool WindowsSystemClass::InitializeWindow()
{
	assert(m_bCurrentState != WindowsOSState::INITIALIZED);

	//Allow this method to be idempotent.
	if (m_bCurrentState == WindowsOSState::INITIALIZED)
	{
		WriteToLog("[WindowsSystemClass::InitializeWindow] The window has already been initialized.", LogLevelType::Diagnostic);
		return true;
	}

	WriteToLog("[WindowsSystemClass::InitializeWindow] Attempting to create a window.", LogLevelType::Diagnostic);

	// Get the instance of this application.
	m_hInstance = GetModuleHandle(nullptr);

	//We're screwed if this happens.
	if (m_hInstance == nullptr)
	{
		throw NullArgumentException("WindowsSystemClass", "InitializeWindow", "m_hInstance");
	}

	// Initialize global strings
	LoadString(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadString(m_hInstance, IDC_COFFEEENGINE, m_szWindowClass, MAX_LOADSTRING);

	RegisterWindowsClass(m_hInstance);

	//Create a window half the size of the desktop.
	m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;

	//Center the window.
	int xPos = m_nScreenWidth / 2;
	int yPos = m_nScreenHeight / 2;

	//Create a window with the following parameters.
	m_hWnd = CreateWindowEx(WS_EX_WINDOWEDGE,			//The Extended Style of the window.
		m_szWindowClass,			//The name of the class.
		m_szTitle,					//The name of the window.
		WS_OVERLAPPEDWINDOW,		//The style of the window.
		xPos,						//The x coordinate of the window.
		yPos,						//The y coordinate of the window.
		m_nScreenWidth,				//The width of the window.
		m_nScreenHeight,			//The height of the window.
		nullptr, nullptr,			//The handle to the parent & menu.
		m_hInstance, nullptr);		//The instance of the window program & child info.

	if (m_hWnd)
	{
		ShowWindow(m_hWnd, SW_SHOW);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);
		UpdateWindow(m_hWnd);

		//We are now active and initialized.
		m_bIsActive = true;
		m_bCurrentState = WindowsOSState::INITIALIZED;

		return true;
	}

	WriteToLog("[WindowsSystemClass::InitializeWindow] Window creation failed!", LogLevelType::Error);
	return false;
}

std::string WindowsSystemClass::GetLastErrorMessage() const
{
	LPVOID lpMsgBuf = nullptr;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&lpMsgBuf,
		0, nullptr);

	//const char* test = (const char*)lpMsgBuf;
	std::wstring wstr = std::wstring((wchar_t*)lpMsgBuf);

	LocalFree(lpMsgBuf);

	//Remove the CR-LF.
	return std::string(wstr.begin(), wstr.end() - 2);
}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////
void WindowsSystemClass::RegisterWindowsClass(HINSTANCE hInstance)
{
	assert(hInstance != nullptr);

	//Register the windows class.
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_COFFEEENGINE);
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassEx(&wcex);
}

////////////////////////////////////////////////////////////
//
//                INTERNAL MESSAGE HANDLER
// 
////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowsSystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			WriteToLog("[WindowsSystemClass::MessageHandler] Exit command event received.", LogLevelType::Diagnostic);
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		//WriteToLog("[WindowsSystemClass::MessageHandler] Begin Paint.", LogLevelType::Diagnostic);
		BeginPaint(hWnd, &ps);

		if (m_pListener != nullptr)
			m_pListener->OnIdle(true);

		EndPaint(hWnd, &ps);

		//WriteToLog("[WindowsSystemClass::MessageHandler] End Paint.", LogLevelType::Diagnostic);
	}
	break;

	case WM_ACTIVATEAPP:
		m_bIsActive = (bool)wParam;
		break;

	case WM_CLOSE:
		WriteToLog("[WindowsSystemClass::MessageHandler] Close event received.", LogLevelType::Diagnostic);
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		WriteToLog("[WindowsSystemClass::MessageHandler] Destroy event received.", LogLevelType::Diagnostic);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
