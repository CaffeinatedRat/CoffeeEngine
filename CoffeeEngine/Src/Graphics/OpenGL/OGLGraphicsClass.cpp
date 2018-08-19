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

bool OGLGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters)
{
	if(m_pSystem == nullptr)
		throw NullArgumentException("OGLGraphicsClass", "Initialize", "m_pSystem");

	m_pSystem->WriteToLog("[OGLGraphicsClass::Initialize] Begin", LogLevelType::Diagnostic);

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

	SetViewport(0, 0, m_graphicsPresentationProperties.screenWidth, m_graphicsPresentationProperties.screenHeight);

	//Get the actual version, which may not be what we've requested.
	int version[2] = { 0,0 };
	glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
	glGetIntegerv(GL_MINOR_VERSION, &version[1]);

	//Record the actual version information.
	std::stringstream stringstream;
	stringstream << "Actual Version: " << version[0] << "." << version[1] << " [OGLV: " << glGetString(GL_VERSION) << " GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "]";
	m_actualVersionInfo = stringstream.str();

	m_pSystem->WriteToLog("[OGLGraphicsClass::Initialize] " + m_actualVersionInfo);
	m_pSystem->WriteToLog("[OGLGraphicsClass::Initialize] End", LogLevelType::Diagnostic);

	//We are ready to draw.
	return (m_displayReady = true);
}

void OGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	//Prevent scene drawing until initialization is complete.
	if(!m_displayReady)
		return;

	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLGraphicsClass::EndScene()
{
	//Prevent scene drawing until initialization is complete.
	if(!m_displayReady)
		return;
}

void OGLGraphicsClass::Shutdown()
{
	m_pSystem->WriteToLog("[OGLGraphicsClass::Shutdown] Begin", LogLevelType::Diagnostic);

	m_displayReady = m_isGlewInitialized = false;
	m_videoCardDescription = "No Information Available.";
	m_actualVersionInfo = "No version info available.";
	m_numberOfModes = 0;

	m_pSystem->WriteToLog("[OGLGraphicsClass::Shutdown] End", LogLevelType::Diagnostic);
}

IModel* OGLGraphicsClass::CreateModel()
{
	return dynamic_cast<IModel*>(new OGLModelClass(this));
}

IShader* OGLGraphicsClass::CreateShader()
{
	return dynamic_cast<IShader*>(new OGLShaderClass(this));
}

ICamera* OGLGraphicsClass::CreateCamera()
{
	return dynamic_cast<ICamera*>(new OGLCameraClass(this));
}

void OGLGraphicsClass::SetMasterCamera(ICamera* camera)
{
	m_displayReady = false;
	m_pMasterCamera = (OGLCameraClass*)camera;
	m_displayReady = true;
}

//std::vector<std::string> OGLGraphicsClass::GetVideoCardInfo() const
//{
//	throw NotImplementedException("OGLGraphicsClass", "GetVideoCardInfo");
//}

/// <summary>
/// Sets the screen dimensions for the graphics presentation properties.
/// </summary>
void OGLGraphicsClass::SetScreenDimensions(int width, int height)
{
	if (height > 0)
	{
		m_graphicsPresentationProperties.screenWidth = width;
		m_graphicsPresentationProperties.screenHeight = height;

		if (m_pMasterCamera != nullptr)
			m_pMasterCamera->UpdateGraphicsProperties();

		//Reset the viewport.
		SetViewport(0, 0, m_graphicsPresentationProperties.screenWidth, m_graphicsPresentationProperties.screenHeight);
	}
}

////////////////////////////////////////////////////////////
//
//                Protected Methods
// 
////////////////////////////////////////////////////////////
bool OGLGraphicsClass::InitializeGlew()
{
	m_pSystem->WriteToLog("[OGLGraphicsClass::InitializeGlew] Begin", LogLevelType::Diagnostic);

	if (!m_isGlewInitialized)
	{
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			m_pSystem->WriteToLog((const char*)glewGetErrorString(err), LogLevelType::Error);
			return false;
		}
		m_isGlewInitialized = true;
	}

	m_pSystem->WriteToLog("[OGLGraphicsClass::InitializeGlew] End", LogLevelType::Diagnostic);

	return true;
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
	glDisable(GL_CULL_FACE);
	return true;
}

void OGLGraphicsClass::SetViewport(int x, int y, int width, int height)
{
	m_pSystem->WriteToLog("[OGLGraphicsClass::SetViewport] Begin", LogLevelType::Diagnostic);
	glViewport(x, y, width, height);
	m_pSystem->WriteToLog("[OGLGraphicsClass::SetViewport] End", LogLevelType::Diagnostic);
}