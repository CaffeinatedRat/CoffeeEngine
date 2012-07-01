//--------------------------------------------------------------------------------------
// Description: The OpenGL Graphics class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Global.h"
#include "Graphics\OpenGL\OGLGraphicsClass.h"

#include "Utility\Logger.h"

using namespace CoffeeEngine;
//using namespace CoffeeEngine::System;
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
	//m_pMasterCamera = NULL;	

	m_videoCardDescription = "No Information Available.";
}

OGLGraphicsClass::OGLGraphicsClass(const OGLGraphicsClass& object)
	: BaseGraphicsClass(object)
{
	//m_pMasterCamera = object.m_pMasterCamera;
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

	// Create an orthographic projection matrix for 2D rendering.
	//D3DXMatrixOrthoLH(&m_orthoMatrix, (float)m_nScreenWidth, (float)m_nScreenHeight, graphicsInitParameters.fScreenNear, graphicsInitParameters.fScreenDepth);

	//We are ready to draw.
	m_bDisplayReady = true;

	return true;
}

void OGLGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	//Prevent scene drawing until initialization is complete.
	if(!m_bDisplayReady)
		return;

	//Compile the clear colors (RGBA) into a single float array.
	float color[] = { red, green, blue, alpha };

	// Clear the back buffer.
	//m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, color);

	// Clear the depth buffer.
	//m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void OGLGraphicsClass::EndScene()
{
	//Prevent scene drawing until initialization is complete.
	if(!m_bDisplayReady)
		return;

	// Present the back buffer to the screen since rendering is complete.
	//m_pSwapChain->Present( ((m_bVsyncEnabled) ? 1 : 0), 0);
}

void OGLGraphicsClass::Shutdown()
{
	m_bDisplayReady = false;

	// Apparently, DirectX11 and possibly DirectX10 is not capable of closing while in fullscreen, so we have to reset the swap chain to windowed mode before we can release it.
	// According to www.DirectXTutorials.com, this is due to a implicit threading issue.
	//if(m_pSwapChain)
	//{
	//	m_pSwapChain->SetFullscreenState(false, NULL);
	//}

	////Release all of our modes.
	//SAFE_ARRAY_DELETE(m_pDisplayModeList);

	////Safely release all of our dependencies.
	//SAFE_RELEASE(m_pSwapChain);

	//SAFE_RELEASE(m_pRasterState);
	//SAFE_RELEASE(m_pDepthStencilView);
	//SAFE_RELEASE(m_pDepthStencilState);
	//SAFE_RELEASE(m_pDepthStencilBuffer);
	//SAFE_RELEASE(m_pRenderTargetView);
	//SAFE_RELEASE(m_pDevice);
	//SAFE_RELEASE(m_pDeviceContext);

	m_videoCardDescription = "No Information Available.";
	m_nNumOfModes = 0;
}

IModel* OGLGraphicsClass::CreateModel()
{
	throw NotImplementedException("OGLGraphicsClass", "CreateModel");
	//return ((IModel*)new D3DModelClass(this));
}

IShader* OGLGraphicsClass::CreateShader()
{
	throw NotImplementedException("OGLGraphicsClass", "CreateShader");
	//return ((IShader*)new D3DShaderClass(this));
}

ICamera* OGLGraphicsClass::CreateCamera()
{
	throw NotImplementedException("OGLGraphicsClass", "CreateCamera");
	//return ((ICamera*)new D3DCameraClass(this));
}

void OGLGraphicsClass::SetMasterCamera(ICamera* camera)
{
	m_bDisplayReady = false;

	//m_pMasterCamera = (D3DCameraClass*)camera;

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
	return true;
}