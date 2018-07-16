//--------------------------------------------------------------------------------------
// Description: The OpenGL Graphics class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "Utility/Logger.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLModelClass.hpp"
#include "OGLShaderClass.hpp"
#include "OGLCameraClass.hpp"
#include "OGLCommon.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Utility;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
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
	if(m_pSystem == nullptr)
		throw NullArgumentException("OGLGraphicsClass", "Initialize", "m_pSystem");

	m_pSystem->WriteToLog("[OGLGraphicsClass::Initialize] Beginning initialization.");

	m_nScreenWidth = graphicsInitParameters.nScreenWidth;
	m_nScreenHeight = graphicsInitParameters.nScreenHeight;
	m_bVsyncEnabled = graphicsInitParameters.bVsync;
	m_bFullScreen = graphicsInitParameters.bFullscreen;
	m_version.nMajor = graphicsInitParameters.version.nMajor;
	m_version.nMinor = graphicsInitParameters.version.nMinor;

	//Initialize Glew only once.
	if (!OGLGraphicsClass::InitializeGlew())
	{
		return false;
	}

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

	m_pSystem->WriteToLog("[OGLGraphicsClass::Initialize] Ending initialization.");

	return true;
}

void OGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	//Prevent scene drawing until initialization is complete.
	if(!m_bDisplayReady)
		return;

	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLGraphicsClass::EndScene()
{
	//Prevent scene drawing until initialization is complete.
	if(!m_bDisplayReady)
		return;
}

void OGLGraphicsClass::Shutdown()
{
	m_pSystem->WriteToLog("[OGLGraphicsClass::Shutdown] Shutting down...");

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
	return dynamic_cast<ICamera*>(new OGLCameraClass(this));
}

void OGLGraphicsClass::SetMasterCamera(ICamera* camera)
{
	m_bDisplayReady = false;

	m_pMasterCamera = (OGLCameraClass*)camera;

	m_bDisplayReady = true;
}

std::vector<std::string> OGLGraphicsClass::GetVideoCardInfo() const
{
	throw NotImplementedException("OGLGraphicsClass", "GetVideoCardInfo");
}

////////////////////////////////////////////////////////////
//
//                Protected Methods
// 
////////////////////////////////////////////////////////////
bool OGLGraphicsClass::InitializeGlew()
{
	m_pSystem->WriteToLog("[OGLGraphicsClass::InitializeGlew] Beginning...");

	if (!m_bGlewInitialized)
	{
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			m_pSystem->WriteToLog((const char*)glewGetErrorString(err), LogLevelType::Error);
			return false;
		}
		m_bGlewInitialized = true;
	}

	m_pSystem->WriteToLog("[OGLGraphicsClass::InitializeGlew] Completed.");

	return true;
}

void OGLGraphicsClass::InitializeGLContext()
{

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
	m_pSystem->WriteToLog("[OGLGraphicsClass::CreateViewPort] Beginning...");

	glViewport(0, 0, m_nScreenWidth, m_nScreenHeight);

	m_pSystem->WriteToLog("[OGLGraphicsClass::CreateViewPort] Completed successfully.");

	return true;
}