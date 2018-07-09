//--------------------------------------------------------------------------------------
// Description: The Windows OpenGL Graphics class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#include "Common.hpp"
#include "Utility/Logger.hpp"
#include "WinOGLGraphicsClass.hpp"
#include "System/Win32/WindowsSystemClass.hpp"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <gl/glew.h>
#include <gl/wglew.h>

using namespace CoffeeEngine;
using namespace CoffeeEngine::Utility;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

LRESULT CALLBACK MessageHandlerGlew(HWND, UINT, WPARAM, LPARAM);

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
WinOGLGraphicsClass::WinOGLGraphicsClass(const WinOGLGraphicsClass& object)
	: OGLGraphicsClass(object)
{
	m_renderingContext = object.m_renderingContext;
	m_hdc = object.m_hdc;
}

WinOGLGraphicsClass::~WinOGLGraphicsClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////
bool WinOGLGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters)
{
	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);
	if (pSystem == nullptr)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_pSystem");

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] Beginning initialization.");

	m_nScreenWidth = graphicsInitParameters.nScreenWidth;
	m_nScreenHeight = graphicsInitParameters.nScreenHeight;
	m_bVsyncEnabled = graphicsInitParameters.bVsync;
	m_bFullScreen = graphicsInitParameters.bFullscreen;
	m_version.nMajor = graphicsInitParameters.version.nMajor;
	m_version.nMinor = graphicsInitParameters.version.nMinor;

	//if (!InitializeGlew())
	//	return false;

	//Get the main device context for our current window.
	m_hdc = GetDC(pSystem->GetHWND());
	assert(m_hdc);
	if (m_hdc == nullptr)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_hdc");

	//Initialize OpenGL based on the verison number.
	PIXELFORMATDESCRIPTOR pfd;
	bool initializationStatus = false;

	//Initialized OpenGL version 3.0 and greater, as long as the glew context & formats are supported.
	if (m_version.nMajor > 2 && WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		{
			pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] Vertex & Fragment shaders supported.", LogLevelType::Informational);
		}

		const int iPixelFormats[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, graphicsInitParameters.nColorBits,
			WGL_DEPTH_BITS_ARB, graphicsInitParameters.nDepthBits,
			WGL_STENCIL_BITS_ARB, 8,
			0 // End of attributes list
		};

		int pixelFormat = 0, numberOfFormats = 0;
		wglChoosePixelFormatARB(m_hdc, iPixelFormats, NULL, 1, &pixelFormat, (UINT*)&numberOfFormats);
		assert(pixelFormat > 0);
		if (pixelFormat > 0)
		{
			bool bResult = SetPixelFormat(m_hdc, pixelFormat, &pfd);
			assert(bResult);
			if (bResult)
			{
				int iContextAttributes[] =
				{
					WGL_CONTEXT_MAJOR_VERSION_ARB, m_version.nMajor,
					WGL_CONTEXT_MINOR_VERSION_ARB, m_version.nMinor,
					WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
					0
				};

				m_renderingContext = wglCreateContextAttribsARB(m_hdc, 0, iContextAttributes);
				assert(m_renderingContext);
				if (m_renderingContext == nullptr)
				{
					pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] The OpenGL version 3 context could not be created.", LogLevelType::Error);
					return false;
				}

				bResult = wglMakeCurrent(m_hdc, m_renderingContext);
				assert(bResult);

				//Call the parent class.
				initializationStatus = OGLGraphicsClass::Initialize(graphicsInitParameters);
			}
		}
	}
	//Initialize OpenGL version 2.0 or fall back to 2.0 if the enhanced OpenGL methods are not available.
	else
	{
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = graphicsInitParameters.nColorBits;
		pfd.cDepthBits = graphicsInitParameters.nDepthBits;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
		assert(pixelFormat > 0);
		if (pixelFormat > 0)
		{
			bool bResult = SetPixelFormat(m_hdc, pixelFormat, &pfd);
			assert(bResult);
			if (bResult)
			{
				m_renderingContext = wglCreateContext(m_hdc);
				assert(m_renderingContext);
				if (m_renderingContext == nullptr)
				{
					pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] The OpenGL version 2 context could not be created.", LogLevelType::Error);
					return false;
				}
				
				bResult = wglMakeCurrent(m_hdc, m_renderingContext);
				assert(bResult);

				//Call the parent class.
				initializationStatus = OGLGraphicsClass::Initialize(graphicsInitParameters);
			}
		}
	}

	//Get the actual version, which may not be what we've requested.
	int version[2];
	glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
	glGetIntegerv(GL_MINOR_VERSION, &version[1]);

	//Record the actual version information.
	std::stringstream stringstream;
	stringstream << "Actual Version: " << version[0] << "." << version[1];
	m_actualVersionInfo = stringstream.str();

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] " + m_actualVersionInfo);
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] Ending initialization.");
	return initializationStatus;
}

void WinOGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	OGLGraphicsClass::BeginScene(red, green, blue, alpha);
}

void WinOGLGraphicsClass::EndScene()
{
	if (m_bDisplayReady)
	{
		OGLGraphicsClass::EndScene();
		SwapBuffers(m_hdc);
	}
}

void WinOGLGraphicsClass::Shutdown()
{
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Shutdown] Shutting down...");

	//Clean up the OpenGL Context.
	if (m_renderingContext != nullptr)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = nullptr;
	}

	//Clean up the HDC as well.
	if (m_hdc != nullptr)
	{
		auto pSystem = dynamic_cast<const WindowsSystemClass*>(m_pSystem);
		assert(pSystem);
		ReleaseDC(pSystem->GetHWND(), m_hdc);
		m_hdc = nullptr;
	}

	OGLGraphicsClass::Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Protected Methods
// 
////////////////////////////////////////////////////////////
bool WinOGLGraphicsClass::InitializeGlew()
{
	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);

	HINSTANCE systemHInstance = pSystem->GetHInstance();
	assert(systemHInstance);

	HWND systemHWND = pSystem->GetHWND();
	assert(systemHWND);

	RegisterGlewClass(systemHInstance);

	HWND placeHolderHWND = CreateWindow(WinOGLGraphicsClass::GLEW_CLASS_NAME
		, WinOGLGraphicsClass::GLEW_CLASS_NAME
		, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPCHILDREN
		, 0
		, 0
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, nullptr
		, nullptr
		, systemHInstance
		, nullptr);

	if (placeHolderHWND == nullptr)
	{
		m_pSystem->WriteToLog("[WinOGLGraphicsClass::InitializeGlew] Glew window could not be created.");
		return false;
	}

	// First, choose false pixel format
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);

	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	bool glewResults = false;
	HDC placeHolderHDC = GetDC(placeHolderHWND);
	int iPixelFormat = ChoosePixelFormat(placeHolderHDC, &pfd);
	if (iPixelFormat > 0)
	{
		if (SetPixelFormat(placeHolderHDC, iPixelFormat, &pfd))
		{
			// Create the false, old style context (OpenGL 2.1 and before)
			HGLRC hglrc = wglCreateContext(placeHolderHDC);
			wglMakeCurrent(placeHolderHDC, hglrc);

			if (!(glewResults = OGLGraphicsClass::InitializeGlew()))
			{
				MessageBox(systemHWND, _T("Couldn't initialize GLEW!"), _T("Fatal Error"), MB_ICONERROR);
			}

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hglrc);
			DestroyWindow(placeHolderHWND);
		}
	}

	return glewResults;
}


////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////
void WinOGLGraphicsClass::RegisterGlewClass(HINSTANCE hInstance)
{
	assert(hInstance != nullptr);

	if (!m_bGlewClassRegistered)
	{
		WNDCLASSEX wc;

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wc.lpfnWndProc = MessageHandlerGlew;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_MENUBAR + 1);
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = WinOGLGraphicsClass::GLEW_CLASS_NAME;
		RegisterClassEx(&wc);

		m_bGlewClassRegistered = true;
	}
}

LRESULT CALLBACK MessageHandlerGlew(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		//WriteToLog("[WindowsSystemClass::MessageHandler] Begin Paint.", LogLevelType::DeepDiagnostic);
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		//WriteToLog("[WindowsSystemClass::MessageHandler] End Paint.", LogLevelType::DeepDiagnostic);
	}
	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

#endif