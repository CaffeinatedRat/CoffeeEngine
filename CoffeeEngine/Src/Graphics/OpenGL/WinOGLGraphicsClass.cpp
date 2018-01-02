//--------------------------------------------------------------------------------------
// Description: The Windows OpenGL Graphics class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.h"
#include "Utility/Logger.h"
#include "Graphics/OpenGL/WinOGLGraphicsClass.h"
#include "System/Win32/WindowsSystemClass.h"

#pragma comment(lib,"opengl32.lib")

using namespace CoffeeEngine;
using namespace CoffeeEngine::Utility;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

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
	OGLGraphicsClass::Shutdown();
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////
bool WinOGLGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters)
{
	if (m_pSystem == nullptr)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_pSystem");

	//Create the windows context device, which is needed in order to run OpenGL in windows.
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	m_hdc = GetDC(pSystem->GetHWND());

	if (m_hdc == nullptr)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_hdc");

	int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	assert(pixelFormat > 0);

	if (pixelFormat > 0)
	{
		bool bResult = false;
		assert(bResult = SetPixelFormat(m_hdc, pixelFormat, &pfd));
		if (bResult)
		{
			assert((m_renderingContext = wglCreateContext(m_hdc)) != nullptr);
			if (m_renderingContext == nullptr)
			{
				pSystem->WriteToLog("[WinOGLGraphicsClass::Initialize] The OpenGL Context could not be created.", LogLevelType::Error);
				return false;
			}

			assert(bResult = wglMakeCurrent(m_hdc, m_renderingContext));

			//Call the parent class.
			return OGLGraphicsClass::Initialize(graphicsInitParameters);
		}
	}

	return false;
}

void WinOGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	OGLGraphicsClass::BeginScene(red, green, blue, alpha);
}

void WinOGLGraphicsClass::EndScene()
{
	OGLGraphicsClass::EndScene();
	SwapBuffers(m_hdc);
}

void WinOGLGraphicsClass::Shutdown()
{
	//Clean up the OpenGL Context.
	if (m_renderingContext != nullptr)
	{
		wglDeleteContext(m_renderingContext);
		m_renderingContext = nullptr;
	}

	//Clean up the HDC as well.
	if (m_hdc != nullptr)
	{
		auto pSystem = dynamic_cast<const WindowsSystemClass*>(m_pSystem);
		ReleaseDC(pSystem->GetHWND(), m_hdc);
		m_hdc = nullptr;
	}

	OGLGraphicsClass::Shutdown();
}