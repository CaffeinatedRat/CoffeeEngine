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

//Forward Declarations
LRESULT CALLBACK DummyMessageHandlerGlew(HWND, UINT, WPARAM, LPARAM);

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
bool WinOGLGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters)
{
	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);
	if (pSystem == nullptr)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_pSystem");

	//Get the main device context for our current window.
	m_hdc = GetDC(pSystem->GetHWND());
	assert(m_hdc);
	if (m_hdc == nullptr)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_hdc");

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] Begin", LogLevelType::Diagnostic);

	BaseGraphicsClass::Initialize(graphicsInitParameters);

	//Initialize OpenGL based on the verison number.
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.cColorBits = graphicsInitParameters.colorBits;
	pfd.cDepthBits = graphicsInitParameters.depthBits;

	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] Vertex & Fragment shaders supported.", LogLevelType::Informational);
	}

	int iContextAttributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, graphicsInitParameters.version.nMajor,
		WGL_CONTEXT_MINOR_VERSION_ARB,  graphicsInitParameters.version.nMinor,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	bool initializationStatus = false;
	bool newerOpenGLVersion = (graphicsInitParameters.version.nMajor > 2);//&& WGLEW_ARB_create_context && WGLEW_ARB_pixel_format);

	//Get the pixel format based on the version of OpenGL.
	//int pixelFormat = newerOpenGLVersion ? GetPixelFormat(graphicsInitParameters) : ChoosePixelFormat(m_hdc, &pfd);
	int pixelFormat = GetPixelFormat(graphicsInitParameters, pfd);

	if (!OGLGraphicsClass::InitializeGlew())
	{
		pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Couldn't initialize GLEW!", LogLevelType::Error);
		return 0;
	}

	assert(pixelFormat > 0);
	if (pixelFormat > 0)
	{
		if (SetPixelFormat(m_hdc, pixelFormat, &pfd))
		{
			m_renderingContext = newerOpenGLVersion ? wglCreateContextAttribsARB(m_hdc, 0, iContextAttributes) : wglCreateContext(m_hdc);
			assert(m_renderingContext);
			if (m_renderingContext != nullptr)
			{
				initializationStatus = true;
			}
			else
			{
				pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] The OpenGL version context could not wglCreateContext or wglCreateContextAttribsARB.", LogLevelType::Error);
			}
		}
		else
		{
			pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] The OpenGL version could not SetPixelFormat.", LogLevelType::Error);
		}
	}

	if (initializationStatus && wglMakeCurrent(m_hdc, m_renderingContext))
	{
		if (OGLGraphicsClass::Initialize(graphicsInitParameters))
		{
			m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] End", LogLevelType::Diagnostic);
			return true;
		}
	}

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] Failed!", LogLevelType::Error);
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] End", LogLevelType::Diagnostic);
	return false;
}

void WinOGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	OGLGraphicsClass::BeginScene(red, green, blue, alpha);
}

void WinOGLGraphicsClass::EndScene()
{
	if (m_displayReady)
	{
		OGLGraphicsClass::EndScene();
		SwapBuffers(m_hdc);
	}
}

void WinOGLGraphicsClass::Shutdown()
{
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Shutdown] Begin", LogLevelType::Diagnostic);

	OGLGraphicsClass::Shutdown();

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

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::Shutdown] End", LogLevelType::Diagnostic);
}

////////////////////////////////////////////////////////////
//
//                Protected Methods
// 
////////////////////////////////////////////////////////////
int WinOGLGraphicsClass::GetPixelFormat(const CoffeeEngine::Graphics::GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters, PIXELFORMATDESCRIPTOR& pfd)
{
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::GetPixelFormat] Begin", LogLevelType::Diagnostic);

	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);

	bool newerOpenGLVersion = (graphicsInitParameters.version.nMajor > 2);//&& WGLEW_ARB_create_context && WGLEW_ARB_pixel_format);

	int pixelFormat = 0, numberOfFormats = 0;
	if (newerOpenGLVersion)
	{
		if (!CreateGlewDummyWindow())
			return 0;

		const int iPixelFormats[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, graphicsInitParameters.colorBits,
			//WGL_DEPTH_BITS_ARB, graphicsInitParameters.depthBits,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_ALPHA_BITS_ARB, graphicsInitParameters.alphaBits,
			WGL_STENCIL_BITS_ARB, graphicsInitParameters.stencilBits,
			WGL_SAMPLE_BUFFERS_ARB, graphicsInitParameters.numberOfSamples > 0 ? 1 : 0,
			WGL_SAMPLES_ARB, graphicsInitParameters.numberOfSamples,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			0 // End of attributes list
		};

		//Initialize Glew early since we need to use the extension for choosing a pixel format.
		//NOTE: This method is idempotent and should have no side effects if it is called multiple times.
		if (OGLGraphicsClass::InitializeGlew())
		{
			bool status = wglChoosePixelFormatARB(m_hdc, iPixelFormats, NULL, 1, &pixelFormat, (uint*)&numberOfFormats);
			pixelFormat = (status && numberOfFormats > 0) ? pixelFormat : 0;
		}
		else
		{
			m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Couldn't initialize GLEW!", LogLevelType::Error);
		}

		DestroyGlewDummyWindow();
	}
	else
	{
		pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	}

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::GetPixelFormat] End", LogLevelType::Diagnostic);
	return pixelFormat;
}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////
void WinOGLGraphicsClass::RegisterGlewClass(HINSTANCE hInstance)
{
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::RegisterGlewClass] Begin", LogLevelType::Diagnostic);

	assert(hInstance);

	if (!m_glewDummyInfo.glewRegistered)
	{
		m_glewDummyInfo.wndClass.cbSize = sizeof(WNDCLASSEX);
		m_glewDummyInfo.wndClass.style = CS_OWNDC;
		m_glewDummyInfo.wndClass.cbClsExtra = 0;
		m_glewDummyInfo.wndClass.cbWndExtra = 0;
		m_glewDummyInfo.wndClass.lpfnWndProc = DummyMessageHandlerGlew;
		m_glewDummyInfo.wndClass.hInstance = hInstance;
		m_glewDummyInfo.wndClass.hIcon = nullptr;
		m_glewDummyInfo.wndClass.hIconSm = nullptr;
		m_glewDummyInfo.wndClass.hCursor = nullptr;
		m_glewDummyInfo.wndClass.hbrBackground = (HBRUSH)(COLOR_MENUBAR + 1);
		m_glewDummyInfo.wndClass.lpszMenuName = nullptr;
		m_glewDummyInfo.wndClass.lpszClassName = WinOGLGraphicsClass::GLEW_CLASS_NAME;
		RegisterClassEx(&m_glewDummyInfo.wndClass);

		m_glewDummyInfo.glewRegistered = true;
	}

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::RegisterGlewClass] End", LogLevelType::Diagnostic);
}

void WinOGLGraphicsClass::UnregisterGlewClass(HINSTANCE hInstance)
{
	assert(hInstance);
	if (m_glewDummyInfo.glewRegistered)
	{
		UnregisterClass(WinOGLGraphicsClass::GLEW_CLASS_NAME, hInstance);
		m_glewDummyInfo.glewRegistered = false;
	}
}

bool WinOGLGraphicsClass::CreateGlewDummyWindow()
{
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Begin", LogLevelType::Diagnostic);

	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);

	HINSTANCE systemHInstance = pSystem->GetHInstance();
	assert(systemHInstance);

	RegisterGlewClass(systemHInstance);

	if (m_glewDummyInfo.hwnd == nullptr)
	{
		m_glewDummyInfo.hwnd = CreateWindow(WinOGLGraphicsClass::GLEW_CLASS_NAME
			, WinOGLGraphicsClass::GLEW_CLASS_NAME
			, WS_OVERLAPPEDWINDOW
			, 0
			, 0
			, 0
			, 0
			, nullptr
			, nullptr
			, systemHInstance
			, nullptr);

		if (m_glewDummyInfo.hwnd == nullptr)
		{
			UnregisterGlewClass(systemHInstance);
			m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Glew placeholder window could not be created.", LogLevelType::Error);
			return false;
		}

		// First, choose false pixel format
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;

		m_glewDummyInfo.hdc = GetDC(m_glewDummyInfo.hwnd);
		int iPixelFormat = ChoosePixelFormat(m_glewDummyInfo.hdc, &pfd);
		if (iPixelFormat > 0)
		{
			if (SetPixelFormat(m_glewDummyInfo.hdc, iPixelFormat, &pfd))
			{
				// Create a fake context and make it current.
				m_glewDummyInfo.hrc = wglCreateContext(m_glewDummyInfo.hdc);
				if (wglMakeCurrent(m_glewDummyInfo.hdc, m_glewDummyInfo.hrc))
				{
					m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] End", LogLevelType::Diagnostic);
					return true;
				}

				m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Coult not make current context.", LogLevelType::Error);
			}
			else
			{
				m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Could not SetPixelFormat.", LogLevelType::Error);
			}
		}
		else
		{
			m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] Could not ChoosePixelFormat.", LogLevelType::Error);
		}

		//Handle error states.
		DestroyGlewDummyWindow();
		return false;
	}

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::CreateDummyWindow] End", LogLevelType::Diagnostic);
	return true;
}

void WinOGLGraphicsClass::DestroyGlewDummyWindow()
{
	m_pSystem->WriteToLog("[WinOGLGraphicsClass::DestroyDummyWindow] Begin", LogLevelType::Diagnostic);

	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);

	HINSTANCE systemHInstance = pSystem->GetHInstance();
	assert(systemHInstance);

	if (m_glewDummyInfo.hrc != nullptr)
	{
		wglMakeCurrent(m_glewDummyInfo.hdc, nullptr);
		wglDeleteContext(m_glewDummyInfo.hrc);
		m_glewDummyInfo.hrc = nullptr;
	}
	
	if (m_glewDummyInfo.hdc != nullptr)
	{
		ReleaseDC(m_glewDummyInfo.hwnd, m_glewDummyInfo.hdc);
		m_glewDummyInfo.hdc = nullptr;
	}

	if (m_glewDummyInfo.hwnd != nullptr)
	{
		DestroyWindow(m_glewDummyInfo.hwnd);
		m_glewDummyInfo.hwnd = nullptr;
	}

	UnregisterGlewClass(systemHInstance);

	m_pSystem->WriteToLog("[WinOGLGraphicsClass::DestroyDummyWindow] End", LogLevelType::Diagnostic);
}

LRESULT CALLBACK DummyMessageHandlerGlew(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;

	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

#endif