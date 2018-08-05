//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

//Windows specific.
#include "../Resources/Resource.h"

#include "Common.hpp"
#include "Utility/Logger.hpp"
#include "Graphics/GraphicsCommon.hpp"

#include "Windows_EntryPoint.hpp"
#include "WindowsSystemClass.hpp"
#include "TimerClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Utility;
using namespace CoffeeEngine::Utility::Logging;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

WindowsSystemClass::WindowsSystemClass(Logger *pLogger)
{
	assert(pLogger);
	if (pLogger == nullptr)
		throw NullArgumentException("WindowsSystemClass", "Constructor", "pLogger");

	m_pLogger = pLogger;
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
	assert(listener);
	if (listener == nullptr)
		throw NullArgumentException("WindowsSystemClass", "Initialize", "listener");

	WriteToLog("[WindowsSystemClass::Initialize] Begin");

	//Allow this method to be idempotent.
	if (m_state == WindowsOSState::SHUTDOWN)
	{
		m_pListener = listener;

		//Attempt to initialize the window.
		if (!InitializeWindow())
		{
			WriteToLog("[WindowsSystemClass::Initialize] Failed!", LogLevelType::Error);
			return false;
		}

		m_state = WindowsOSState::INITIALIZED;
	}

	WriteToLog("[WindowsSystemClass::Initialize] End");
	return true;
}

void WindowsSystemClass::Run()
{
	WriteToLog("[WindowsSystemClass::Run] Begin");

	if (m_state == WindowsOSState::INITIALIZED)
	{
		m_state = WindowsOSState::RUNNING;
		WriteToLog("[WindowsSystemClass::Run] Beginning the message pump. State Updated: WindowsOSState::RUNNING.");

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

		WriteToLog("[WindowsSystemClass::Run] Ending the message pump.");
	}

	WriteToLog("[WindowsSystemClass::Run] End");
}

/// <summary>
/// Begins the process of shutting down the OS handler and cleaning up any remaining resources.
/// </summary>
void WindowsSystemClass::Shutdown()
{
	WriteToLog("[WindowsSystemClass::Shutdown] Begin");

	//This flag allows this method to be idempotent.
	if (m_state > WindowsOSState::SHUTDOWN)
	{
		WriteToLog("[WindowsSystemClass::Shutdown] Shutting down...");

		//Clean up the window.
		if (m_hWnd)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = nullptr;
		}

		UnregisterClass(m_szWindowClass, m_hInstance);
		m_state = WindowsOSState::SHUTDOWN;

		WriteToLog("[WindowsSystemClass::Shutdown] State Updated: WindowsOSState::SHUTDOWN.");
	}

	WriteToLog("[WindowsSystemClass::Shutdown] End");
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
	assert(m_pLogger);
	m_pLogger->Write(szEvent, logEventType);
}

/// <summary>
/// Writes an event to the event log.
/// </summary>
/// <param name="sEvent">Event to write to the log.</param>
/// <param name="logEventType">Type of log event.</param>
void WindowsSystemClass::WriteToLog(const std::string& sEvent, LogLevelType logEventType) noexcept
{
	assert(m_pLogger);
	m_pLogger->Write(sEvent, logEventType);
}

void WindowsSystemClass::WriteToLog(const std::stringstream& logEvent, LogLevelType logEventType) noexcept
{
	assert(m_pLogger);
	m_pLogger->Write(logEvent, logEventType);
}

/// <summary>
/// Writes an exception to the event log.
/// </summary>
/// <param name="exception">Exception to write to the log.</param>
/// <param name="logEventType">Type of log event.</param>
void WindowsSystemClass::WriteToLog(Exception& exception) noexcept
{
	assert(m_pLogger);
	m_pLogger->Write(exception);
}

std::string WindowsSystemClass::GetCurrentApplicationDirectory() const
{
	std::string rootDirectory;
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
					rootDirectory = std::string(convertedString);
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

	return rootDirectory;
}

/// <summary>
/// Returns the windows dimension information.
/// </summary>
WindowDimensions WindowsSystemClass::GetWindowDimensions() const
{
	WindowDimensions windowDimensions;
	RECT rect;
	if (GetClientRect(m_hWnd, &rect))
	{
		windowDimensions.x = rect.left;
		windowDimensions.y = rect.top;
		windowDimensions.height = rect.bottom;
		windowDimensions.width = rect.right;
	}
	else
	{
		auto thisCast = const_cast<WindowsSystemClass*>(this);
		if (thisCast)
		{
			std::stringstream errorMessage;
			errorMessage << "[WindowsSystemClass::GetWindowDimensions] " << WindowsSystemClass::GetLastErrorMessage();
			thisCast->WriteToLog(errorMessage, LogLevelType::Error);
		}
	}

	return windowDimensions;
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
	WriteToLog("[WindowsSystemClass::InitializeWindow] Begin");

	// Get the instance of this application.
	m_hInstance = GetModuleHandle(nullptr);

	//We're screwed if this happens.
	assert(m_hInstance);
	if (m_hInstance == nullptr)
		throw NullArgumentException("WindowsSystemClass", "InitializeWindow", "m_hInstance");

	// Initialize global strings
	LoadString(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadString(m_hInstance, IDC_COFFEEENGINE, m_szWindowClass, MAX_LOADSTRING);

	RegisterWindowsClass(m_hInstance);

	//Create a window half the size of the desktop.
	m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;

	//Create a window with the following parameters.
	m_hWnd = CreateWindowEx(WS_EX_WINDOWEDGE,	//The Extended Style of the window.
		m_szWindowClass,						//The name of the class.
		m_szTitle,								//The name of the window.
		WS_OVERLAPPEDWINDOW,					//The style of the window.
		(m_nScreenWidth / 2),					//The x coordinate of the window, horizontally centered.
		(m_nScreenHeight / 2),					//The y coordinate of the window, vertically centered.
		m_nScreenWidth,							//The width of the window.
		m_nScreenHeight,						//The height of the window.
		nullptr, nullptr,						//The handle to the parent & menu.
		m_hInstance, nullptr);					//The instance of the window program & child info.

	if (m_hWnd)
	{
		ShowWindow(m_hWnd, SW_SHOW);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);
		UpdateWindow(m_hWnd);

		//We are now active and initialized.
		WriteToLog("[WindowsSystemClass::InitializeWindow] End");
		return (m_bIsActive = true);
	}

	WriteToLog("[WindowsSystemClass::InitializeWindow] Failed!", LogLevelType::Error);
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

	std::string errorMessage;
	assert(lpMsgBuf != nullptr);
	if (lpMsgBuf != nullptr)
	{
		std::wstring wstr = std::wstring((wchar_t*)lpMsgBuf);

		LocalFree(lpMsgBuf);

		//Remove the CR-LF.
		errorMessage = std::string(wstr.begin(), wstr.end() - 2);
	}

	return errorMessage;
}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////
void WindowsSystemClass::RegisterWindowsClass(HINSTANCE hInstance)
{
	assert(hInstance);
	WriteToLog("[WindowsSystemClass::RegisterWindowsClass] Begin", LogLevelType::Diagnostic);

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
	WriteToLog("[WindowsSystemClass::RegisterWindowsClass] End", LogLevelType::Diagnostic);
}

/// <summary>
/// Translates an OS specific virtaul key into a known keyboard key.
/// </summary>
KeyboardKeys WindowsSystemClass::TranslateKeys(int virtualKey)
{
	switch (virtualKey)
	{
	case VK_BACK:
		return KeyboardKeys::Backspace;
	case VK_ESCAPE:
		return KeyboardKeys::Escape;
	case VK_RETURN:
		return KeyboardKeys::Enter;
	case VK_UP:
		return KeyboardKeys::UpArrow;
	case VK_DOWN:
		return KeyboardKeys::DownArrow;
	case VK_LEFT:
		return KeyboardKeys::LeftArrow;
	case VK_RIGHT:
		return KeyboardKeys::RightArrow;
	case VK_SPACE:
		return KeyboardKeys::Space;
	case VK_TAB:
		return KeyboardKeys::Tab;
	case VK_PAUSE:
		return KeyboardKeys::Pause;
	case VK_CAPITAL:
		return KeyboardKeys::Caps;
	case VK_INSERT:
		return KeyboardKeys::Insert;
	case VK_DELETE:
		return KeyboardKeys::Delete;
	case VK_HOME:
		return KeyboardKeys::Home;
	case VK_END:
		return KeyboardKeys::End;
	case VK_PRIOR:
		return KeyboardKeys::PageUp;
	case VK_NEXT:
		return KeyboardKeys::PageDown;
	case VK_F1:
		return KeyboardKeys::F1;
	case VK_F2:
		return KeyboardKeys::F2;
	case VK_F3:
		return KeyboardKeys::F3;
	case VK_F4:
		return KeyboardKeys::F4;
	case VK_F5:
		return KeyboardKeys::F5;
	case VK_F6:
		return KeyboardKeys::F6;
	case VK_F7:
		return KeyboardKeys::F7;
	case VK_F8:
		return KeyboardKeys::F8;
	case VK_F9:
		return KeyboardKeys::F9;
	case VK_F10:
		return KeyboardKeys::F10;
	case VK_F11:
		return KeyboardKeys::F11;
	case VK_F12:
		return KeyboardKeys::F12;
	case VK_LSHIFT:
		return KeyboardKeys::LeftShift;
	case VK_RSHIFT:
		return KeyboardKeys::RightShift;
	case VK_OEM_3:
		return KeyboardKeys::Tilde;
	//default:
		//return KeyboardKeys::Unknown;
	default:
		return (KeyboardKeys)virtualKey;
	}
}

////////////////////////////////////////////////////////////
//
//                INTERNAL MESSAGE HANDLER
// 
////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowsSystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

		case ID_GRAPHICS_OPENGL:
			WriteToLog("[WindowsSystemClass::MessageHandler] OPENGL command event received.", LogLevelType::Diagnostic);
			if (m_pListener != nullptr)
				m_pListener->OnGraphicsReset(GraphicsAPIType::OPENGL);
			break;

		case ID_GRAPHICS_DIRECTX:
			WriteToLog("[WindowsSystemClass::MessageHandler] DIRECTX command event received.", LogLevelType::Diagnostic);
			if (m_pListener != nullptr)
				m_pListener->OnGraphicsReset(GraphicsAPIType::DIRECTX);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		//WriteToLog("[WindowsSystemClass::MessageHandler] Begin Paint.", LogLevelType::DeepDiagnostic);
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		if (m_pListener != nullptr)
			m_pListener->OnIdle(true);

		EndPaint(hWnd, &ps);
		//WriteToLog("[WindowsSystemClass::MessageHandler] End Paint.", LogLevelType::DeepDiagnostic);
	}
	break;

	case WM_KEYDOWN:
	{
		std::stringstream stream;
		stream << "[WindowsSystemClass::WM_KEYDOWN] Keycode: " << (int)wParam;
		WriteToLog(stream, LogLevelType::Diagnostic);

		if (m_pListener != nullptr)
			m_pListener->OnKeyDown(TranslateKeys((int)wParam));
	}
	break;

	case WM_KEYUP:
	{
		std::stringstream stream;
		stream << "[WindowsSystemClass::WM_KEYUP] Keycode: " << (int)wParam;
		WriteToLog(stream, LogLevelType::Diagnostic);

		if (m_pListener != nullptr)
			m_pListener->OnKeyUp(TranslateKeys((int)wParam));
	}
	break;

	case WM_CHAR:
	{
		if (m_pListener != nullptr)
			m_pListener->OnChar((int)wParam);
	}
	break;

	case WM_SIZE:
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);
		if (m_pListener != nullptr)
			m_pListener->OnWindowResize(width, height);
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

#endif