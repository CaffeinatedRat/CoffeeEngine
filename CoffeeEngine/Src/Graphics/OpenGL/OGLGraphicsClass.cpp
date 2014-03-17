//--------------------------------------------------------------------------------------
// Description: The OpenGL Graphics class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Global.h"
#include "Graphics/OpenGL/OGLGraphicsClass.h"
#include "Graphics/OpenGL/OGLModelClass.h"
#include "Graphics/OpenGL/OGLShaderClass.h"
#include "Graphics/OpenGL/OGLCameraClass.h"

#include "Utility/Logger.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLGraphicsClass::OGLGraphicsClass(ISystem* pSystem) : BaseGraphicsClass(pSystem, "OpenGL")
{
	m_bVsyncEnabled = false;
	m_bFullScreen = false;
	m_nNumOfModes = 0;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	m_videoCardMemory = 0;

	//We are not ready to draw until initialization is complete.
	m_bDisplayReady = false;

	//By default there is no master camera.
	m_pMasterCamera = NULL;	

	m_videoCardDescription = "No Information Available.";
}

OGLGraphicsClass::OGLGraphicsClass(const OGLGraphicsClass& object)
	: BaseGraphicsClass(object)
{
	m_pMasterCamera = object.m_pMasterCamera;
}

OGLGraphicsClass::~OGLGraphicsClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool OGLGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters)
{
	if(m_pSystem == NULL)
		throw NullArgumentException("OGLGraphicsClass", "Initialize", "m_pSystem");

	m_nScreenWidth = graphicsInitParameters.nScreenWidth;
	m_nScreenHeight = graphicsInitParameters.nScreenHeight;
	m_bVsyncEnabled = graphicsInitParameters.bVsync;
	m_bFullScreen = graphicsInitParameters.bFullscreen;

	GLenum err = glewInit();

	if(err != GLEW_OK)
	{
		CoffeeEngine::Utility::Logger::Write((const char*)glewGetErrorString(err));
		return false;
	}

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if(!CreateModeList())
	{
		Shutdown();
		return false;
	}

	if(!CreateSwapChain())
	{
		Shutdown();
		return false;
	}

	if(!CreateDepthBuffer())
	{
		Shutdown();
		return false;
	}

	if(!CreateRasterState())
	{
		Shutdown();
		return false;
	}

	if(!CreateViewPort())
	{
		Shutdown();
		return false;
	}

	//We are ready to draw.
	m_bDisplayReady = true;

	return true;
}

void OGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	//Prevent scene drawing until initialization is complete.
	if(!m_bDisplayReady)
		return;

	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
}

void OGLGraphicsClass::EndScene()
{
	//Prevent scene drawing until initialization is complete.
	if(!m_bDisplayReady)
		return;

	glEnd();
}

void OGLGraphicsClass::Shutdown()
{
	m_bDisplayReady = false;

	m_videoCardDescription = "No Information Available.";
	m_nNumOfModes = 0;
}

IModel* OGLGraphicsClass::CreateModel()
{
	return ((IModel*)new OGLModelClass(this));
}

IShader* OGLGraphicsClass::CreateShader()
{
	return ((IShader*)new OGLShaderClass(this));
}

ICamera* OGLGraphicsClass::CreateCamera()
{
	return ((ICamera*)new OGLCameraClass(this));
}

void OGLGraphicsClass::SetMasterCamera(ICamera* camera)
{
	m_bDisplayReady = false;

	m_pMasterCamera = (OGLCameraClass*)camera;

	m_bDisplayReady = true;
}

std::vector<std::string> OGLGraphicsClass::GetVideoCardInfo()
{
	throw NotImplementedException("OGLGraphicsClass", "GetVideoCardInfo");
}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////

bool OGLGraphicsClass::CreateModeList()
{
	return true;
}

bool OGLGraphicsClass::CreateSwapChain()
{
	return true;
}

bool OGLGraphicsClass::CreateDepthBuffer()
{
	return true;
}

bool OGLGraphicsClass::CreateRasterState()
{
	return true;
}

bool OGLGraphicsClass::CreateViewPort()
{
	glViewport(0, 0, m_nScreenWidth, m_nScreenHeight);
	return true;
}