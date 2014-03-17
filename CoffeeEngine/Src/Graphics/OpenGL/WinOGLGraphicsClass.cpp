//--------------------------------------------------------------------------------------
// Description: The Windows OpenGL Graphics class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Global.h"
#include "Graphics/OpenGL/WinOGLGraphicsClass.h"
#include "System/Win32/WindowsSystemClass.h"

#include "Utility/Logger.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

WinOGLGraphicsClass::WinOGLGraphicsClass(ISystem* pSystem) : OGLGraphicsClass(pSystem)
{
	m_renderingContext = NULL;
	m_hdc = NULL;
}

WinOGLGraphicsClass::WinOGLGraphicsClass(const WinOGLGraphicsClass& object)
	: OGLGraphicsClass(object)
{
	m_renderingContext = object.m_renderingContext;
	m_hdc = object.m_hdc;
}

WinOGLGraphicsClass::~WinOGLGraphicsClass()
{
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////
bool WinOGLGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters)
{
	if(m_pSystem == NULL)
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

	m_hdc = GetDC(((WindowsSystemClass*)m_pSystem)->GetHWND());
	if(m_hdc == NULL)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_hdc");
	
	int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, pixelFormat, &pfd);
	m_renderingContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, m_renderingContext);
	
	if(wglGetCurrentContext() != NULL)
	{
		//Call the parent class.
		return OGLGraphicsClass::Initialize(graphicsInitParameters);
	}
	else
	{
		CoffeeEngine::Utility::Logger::Write("The OpenGL Context could not be created.");
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
	if(m_renderingContext != NULL)
	{
		wglDeleteContext(m_renderingContext);
		m_renderingContext = NULL;
	}

	//Clean up the HDC as well.
	if(m_hdc != NULL)
	{
		ReleaseDC(((WindowsSystemClass*)m_pSystem)->GetHWND(), m_hdc);
		m_hdc = NULL;
	}

	OGLGraphicsClass::Shutdown();
}