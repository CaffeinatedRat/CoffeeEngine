//--------------------------------------------------------------------------------------
// Description: The Windows OpenGL Graphics class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Global.h"
#include "stdafx.h"
#include "Graphics\OpenGL\WinOGLGraphicsClass.h"
#include "System\Win32\WindowsSystemClass.h"

#include "Utility\Logger.h"

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
}

WinOGLGraphicsClass::WinOGLGraphicsClass(const WinOGLGraphicsClass& object)
	: OGLGraphicsClass(object)
{
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
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	HDC hdc = GetDC(((WindowsSystemClass*)m_pSystem)->GetHWND());
	if(hdc == NULL)
		throw NullArgumentException("WinOGLGraphicsClass", "Initialize", "m_pSystem");
	
	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);
	wglMakeCurrent(hdc, wglCreateContext(hdc));
	
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