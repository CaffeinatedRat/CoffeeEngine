//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

//Windows specific.
#include "..\Resources\Resource.h"
#include "System\Win32\Windows_EntryPoint.h"
#include "System\Win32\WindowsSystemClass.h"
#include "Graphics\GraphicsCommon.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\DirectX11\D3DGraphicsClass.h"

#include "Global.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::DirectX11;


////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

WindowsSystemClass::WindowsSystemClass()
{
	m_hInstance = NULL;
	m_hWnd = NULL;
	m_bIsIdle = false;

	m_pGraphics = NULL;
	m_pCoffeeEngine = NULL;
}

WindowsSystemClass::WindowsSystemClass(const WindowsSystemClass& systemClass)
{
	m_hInstance = systemClass.m_hInstance;
	m_hWnd = systemClass.m_hWnd;
	m_bIsIdle = systemClass.m_bIsIdle;

	SAFE_DELETE(m_pGraphics);
	SAFE_DELETE(m_pCoffeeEngine);
	
	//When copying the system class we need to create a new instance of graphics object.
	if((m_pGraphics = new D3DGraphicsClass(this)) == NULL)
		throw Exception("Unable to copy the D3DGraphicsClass");

	//When copying the system class we also need a new copy of the main game engine.
	if ((m_pCoffeeEngine = new CoffeeEngineClass(this, m_pGraphics)) == NULL)
		throw Exception("Unable to copy the CoffeeEngineClass");
}

WindowsSystemClass::~WindowsSystemClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Protected
// 
////////////////////////////////////////////////////////////

bool WindowsSystemClass::InitializeWindow()
{
	// Get the instance of this application.
	m_hInstance = GetModuleHandle(NULL);

	// Initialize global strings
	LoadString(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadString(m_hInstance, IDC_COFFEEENGINE, m_szWindowClass, MAX_LOADSTRING);

	//Register the windows class.
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInstance;
	wcex.hIcon			= LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_COFFEEENGINE);
	wcex.lpszClassName	= m_szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClassEx(&wcex);

	m_nScreenWidth  = GetSystemMetrics(SM_CXSCREEN) / 2;
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;

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
							NULL, NULL,					//The handle to the parent & menu.
							m_hInstance, NULL);			//The instance of the window program & child info.

	if (m_hWnd)
	{
		ShowWindow(m_hWnd, SW_SHOW);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);
		UpdateWindow(m_hWnd);

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////
//
//                Public
// 
////////////////////////////////////////////////////////////

bool WindowsSystemClass::Initialize()
{
	if(!InitializeWindow())
		return false;

	try
	{
		//Attempt to create the D3DGraphics class.
		// TO-DO: Add an option to use an OpenGLGraphicsClass.
		if ( (m_pGraphics = new D3DGraphicsClass(this)) == NULL)
			return false;

		//Attempt to create the main engin and pass the graphics class to the engine.
		if ( (m_pCoffeeEngine = new CoffeeEngineClass(this, m_pGraphics) ) == NULL )
			return false;

		//Parameterize the graphics settings into a structure to reduce the overhead produced by methods with an extremely long number of parameters.
		//NOTE: Temporary initialization...
		GRAPHICS_INITIALIZATION_PARAMETERS graphicsInitParams;
		graphicsInitParams.bFullscreen = false;
		graphicsInitParams.bVsync = true;
		graphicsInitParams.fScreenDepth = 1000.0f;
		graphicsInitParams.fScreenNear = 0.1f;
		graphicsInitParams.nScreenHeight = 480;
		graphicsInitParams.nScreenWidth = 640;

		//Initialize the graphics object first.
		if(!m_pGraphics->Initialize(graphicsInitParams))
			return false;

		//Then initialize the CoffeeEngine, as the graphics object should be available and ready at this time.
		if(!m_pCoffeeEngine->Initialize())
			return false;
	}
	//TO-DO: For testing only, remove when completed...
	catch(Exception& exception)
	{
		std::string message = exception.GetMessage();
		std::wstring temp(message.begin(), message.end());
		throw MessageBox(m_hWnd, temp.c_str(), L"System Error", MB_OK);
	}

	return true;
}

void WindowsSystemClass::Run()
{
	//Begin the windows message pump.
	MSG msg;
	HACCEL hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDC_COFFEEENGINE));

	ZeroMemory(&msg, sizeof(MSG));

	//Fetch early message for quit check, and do not remove it from the message pump.
	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	
	// Begin the main message loop.
	while(msg.message != WM_QUIT)
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Determine if the application is idling and if it is then use the GetMessage API rather than the PeekMessage to prevent CPU pegging.
		if(!m_bIsIdle)
		{
			m_pCoffeeEngine->Run();
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		}
		else
		{
			GetMessage(&msg, NULL, 0, 0);
		}
	}
}

bool WindowsSystemClass::Frame()
{
	if(m_pCoffeeEngine != NULL)
		if(!m_pCoffeeEngine->Frame())
			return false;

	return true;
}

void WindowsSystemClass::Shutdown()
{
	//Clean up the window.
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	UnregisterClass(m_szWindowClass, m_hInstance);

	//Shutdown the graphics & engine.
	if(m_pGraphics != NULL)
		m_pGraphics->Shutdown();

	if(m_pCoffeeEngine != NULL)
		m_pCoffeeEngine->Shutdown();

	 SAFE_DELETE(m_pGraphics);
	 SAFE_DELETE(m_pCoffeeEngine);
}

/// <summary>
/// Writes a message to the OSes console.
/// </summary>
void WindowsSystemClass::ConsoleWrite(std::string sMessage)
{
	std::wstring temp(sMessage.begin(), sMessage.end());
	m_log.push_back(temp);

	if(m_hWnd != NULL)
		InvalidateRect(m_hWnd, NULL, true);
}

std::string WindowsSystemClass::GetCurrentDirectory()
{
	std::string sRootDirectory = "";
	wchar_t* buffer = NULL;
	char* convertedString = NULL;

	try
	{
		//Calculate the need size of the buffer.
		DWORD dwBufferSize = ::GetCurrentDirectory(0, NULL);

		//Allocate memory for the wide character string and return an empty string if no memory could be allocated.
		if ( (buffer = new wchar_t[dwBufferSize]) != NULL)
		{
			DWORD dwStatus = ::GetCurrentDirectory(dwBufferSize, buffer);
			if(dwStatus > 0)
			{
				size_t bufferSize = wcslen(buffer) + 1;
				if ( (convertedString = new char[bufferSize]) != NULL)
				{
					size_t convertedChars = 0;
					wcstombs_s(&convertedChars, convertedString, bufferSize, buffer, _TRUNCATE);
					sRootDirectory = std::string(convertedString);
				}
				//END OF if ( (convertedString = new char[bufferSize]) != NULL)..
			}
			//END OF if(dwStatus > 0)...
		}
		//END OF if ( (buffer = new wchar_t[dwBufferSize]) != NULL)...
	}
	catch(...){}

	SAFE_DELETE(buffer);
	SAFE_DELETE(convertedString);

	return sRootDirectory;
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
			int wmId    = LOWORD(wParam);
			int wmEvent = HIWORD(wParam);
			
			// Parse the menu selections:
			switch (wmId)
			{
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
		
			if(this->m_pCoffeeEngine != NULL)
				this->m_pCoffeeEngine->Frame();
		
			if(m_log.size() > 0)
			{
				std::wstring wsCompiledString;
				for(std::vector<std::wstring>::iterator it = m_log.begin(); it != m_log.end(); it++)
				{
					wsCompiledString.append(*it);
					wsCompiledString.append(L"\r\n");
				}

				RECT rect;
				GetClientRect (hWnd, &rect) ;
				SetTextColor(hdc, 0x00000000);
				SetBkMode(hdc,TRANSPARENT);
				rect.left=0;
				rect.top=0;
				DrawText( hdc, (LPCTSTR)wsCompiledString.c_str(), -1, &rect, DT_WORDBREAK | DT_NOCLIP  ) ;
				DeleteDC(hdc); 
			}

			EndPaint(hWnd, &ps);
		}
		break;

	case WM_ACTIVATEAPP:
		m_bIsIdle = !(BOOL)wParam;
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
