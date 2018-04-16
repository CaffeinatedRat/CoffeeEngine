//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "CoffeeEngineClass.hpp"

#include "Common.hpp"
#include "Utility/Logger.hpp"
#include "System/ISystem.hpp"
#include "Graphics/GraphicsUtility.hpp"
#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/ModelClass.hpp"


using namespace CoffeeEngine;
using namespace CoffeeEngine::Utility;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Engine;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
CoffeeEngineClass::CoffeeEngineClass(ISystem* pSystem)
{
	if (pSystem == nullptr)
		throw NullArgumentException("CoffeeEngineClass", "Constructor", "pSystem");

	m_pSystem = pSystem;
}

CoffeeEngineClass::~CoffeeEngineClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool CoffeeEngineClass::Initialize()
{
	m_pSystem->WriteToLog("[CoffeeEngineClass::Initialize] Initializing...");

	if (!m_pSystem->Initialize(this))
		return false;

	m_pSystem->WriteToLog("[CoffeeEngineClass::Initialize] Attempting to create the graphics device.");

	m_upGraphics = GraphicsFactory::CreateGraphics(GraphicsFactoryTypes::DIRECTX, m_pSystem);
	assert(m_upGraphics);
	if (!m_upGraphics)
		return false;

	//Parameterize the graphics settings into a structure to reduce the overhead produced by methods with an extremely long number of parameters.
	//NOTE: Temporary initialization...
	GRAPHICS_INITIALIZATION_PARAMETERS graphicsInitParams;
	graphicsInitParams.bFullscreen = false;
	graphicsInitParams.bVsync = true;
	graphicsInitParams.fScreenDepth = 1000.0f;
	graphicsInitParams.fScreenNear = 0.1f;
	graphicsInitParams.nColorBits = 32;
	graphicsInitParams.nDepthBits = 32;
	graphicsInitParams.nScreenHeight = 480;
	graphicsInitParams.nScreenWidth = 640;
	graphicsInitParams.version.nMajor = 3;
	graphicsInitParams.version.nMinor = 1;

	//Initialize the graphics object first.
	if (!m_upGraphics->Initialize(graphicsInitParams))
		return false;

	//Create the system timer.
	m_pTimer = m_pSystem->CreateTimer();
	if(!m_pTimer->Start())
		return false;

	m_pCamera = m_upGraphics->CreateCamera();
	if(!m_pCamera->Initialize())
		return false;

	m_upGraphics->SetMasterCamera(m_pCamera);

	m_pModel = m_upGraphics->CreateModel();
	if(!m_pModel->Initialize())
		return false;

	m_pShader = m_upGraphics->CreateShader();
	if(!m_pShader->Initialize("Default.fx"))
		return false;

	return (m_bReady = true);
}

void CoffeeEngineClass::Run()
{
	//Begin the system's message pump.
	m_pSystem->Run();

	//if(m_bReady)
	//{
	//	m_pTimer->Run();
	//	Frame();
	//}
}

void CoffeeEngineClass::Render()
{
	m_pSystem->WriteToLog("[CoffeeEngineClass::Render] Begin Render", LogLevelType::Diagnostic);

	static float rotationY = 0.0f;
	static float rotationX = 0.0f;
	static float rotationZ = 0.0f;

	m_upGraphics->BeginScene(0.0f, 0.3f, 0.7f, 0.5f);

	m_pCamera->Render(m_pTimer->GetElaspedTime());

	//m_pModel->Scale(0.5f, 2.0f, 1.0f);
	m_pModel->Rotate(rotationX, rotationY, rotationZ);
	m_pModel->Translate(-1.0f, 1.0f, 5.0f);
	m_pModel->Render(m_pShader, m_pTimer->GetElaspedTime());

	rotationY += 0.005f;
	rotationX += 0.01f;
	rotationZ += 0.01f;

	m_upGraphics->EndScene();

	m_pSystem->WriteToLog("[CoffeeEngineClass::Render] End Render", LogLevelType::Diagnostic);
}

/// <summary>
/// This event is usually triggered when the OS's message loop is idling and no events are occuring.
/// </summary>
/// <param name="isActive">
/// This parameter indicates if the application is active or running in the background.
/// </param>
void CoffeeEngineClass::OnIdle(bool isActive)
{
	if (m_bReady)
	{
		m_pTimer->Run();
		Render();
	}
}

void CoffeeEngineClass::Shutdown()
{
	m_pSystem->WriteToLog("[CoffeeEngineClass::Shutdown] Shutting down...");

	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pTimer);

	m_bReady = false;
}