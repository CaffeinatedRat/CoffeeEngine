//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "CoffeeEngineClass.hpp"

#include "Common.hpp"
#include "Graphics/GraphicsUtility.hpp"
#include "Graphics/CameraClass.hpp"

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
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::Initialize] Begin", LogLevelType::Diagnostic);

	//Allow this method to be idempotent.
	assert(m_state == EngineState::SHUTDOWN);
	if (m_state == EngineState::SHUTDOWN)
	{
		m_pSystem->WriteToLog("[CoffeeEngineClass::Initialize] Initializing from a shutdown state.");

		if (!m_pSystem->Initialize(this))
			return false;

		//Create the system timer.
		m_pTimer = m_pSystem->CreateTimer();
		if (!m_pTimer->Start())
			return false;

		if (!InitializeGraphics(GraphicsAPIType::DIRECTX))
			return false;

		m_state = EngineState::INITIALIZED;
		m_bReady = true;

		m_pSystem->WriteToLog("[CoffeeEngineClass::Initialize] Engine Ready (m_state == EngineState::INITIALIZED).");
	}

	m_pSystem->WriteToLog("[CoffeeEngineClass::Initialize] End", LogLevelType::Diagnostic);
	return m_bReady;
}

void CoffeeEngineClass::Run()
{
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::Run] Begin", LogLevelType::Diagnostic);

	assert(m_state == EngineState::INITIALIZED);
	if (m_state == EngineState::INITIALIZED)
	{
		m_pSystem->WriteToLog("[CoffeeEngineClass::Run] Starting engine.");

		//Begin the system's message pump and set the state to running.
		m_state = EngineState::RUNNING;
		m_pSystem->WriteToLog("[CoffeeEngineClass::Run] State Updated: EngineState::RUNNING.");
		m_pSystem->Run();	
	}

	m_pSystem->WriteToLog("[CoffeeEngineClass::Run] End", LogLevelType::Diagnostic);
}

void CoffeeEngineClass::Shutdown()
{
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::Shutdown] Begin", LogLevelType::Diagnostic);

	//This flag allows this method to be idempotent.
	if (m_state > EngineState::SHUTDOWN)
	{
		m_pSystem->WriteToLog("[CoffeeEngineClass::Shutdown] Shutting down...");

		SAFE_DELETE(m_pTimer);
		ShutdownGraphicsDisplay();
		m_state = EngineState::SHUTDOWN;
		m_pSystem->WriteToLog("[CoffeeEngineClass::Shutdown] State Updated: EngineState::SHUTDOWN.");
	}

	m_bReady = false;
	m_pSystem->WriteToLog("[CoffeeEngineClass::Shutdown] End", LogLevelType::Diagnostic);
}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////
void CoffeeEngineClass::Render(float elapsedTime)
{
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::Render] Begin", LogLevelType::DeepDiagnostic);

	static float rotationY = 0.0f;
	static float rotationX = 0.0f;
	static float rotationZ = 0.0f;

	m_upGraphics->BeginScene(0.0f, 0.3f, 0.7f, 0.5f);

	m_pCamera->Render(elapsedTime);

	//m_pModel->Scale(0.5f, 2.0f, 1.0f);
	//m_pModel->Rotate(rotationX, rotationY, rotationZ);
	//m_pModel->Translate(-1.0f, 1.0f, 5.0f);
	m_pModel->Render(elapsedTime);

	rotationY += 0.005f;
	rotationX += 0.01f;
	rotationZ += 0.01f;

	m_upGraphics->EndScene();

	m_pSystem->WriteToLog("[CoffeeEngineClass::Render] End", LogLevelType::DeepDiagnostic);
}

void CoffeeEngineClass::ManageWorld(float elapsedTime)
{
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::ManageWorld] Begin", LogLevelType::DeepDiagnostic);

	m_pCamera->Yaw(m_turnMovement);
	m_pCamera->Pitch(m_pitchMovement);
	m_pCamera->Forward(m_forwardMovement);

	m_pSystem->WriteToLog("[CoffeeEngineClass::ManageWorld] End", LogLevelType::DeepDiagnostic);
}

bool CoffeeEngineClass::InitializeGraphics(GraphicsAPIType graphicsType)
{
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::InitializeGraphics] Begin", LogLevelType::Diagnostic);

	m_graphicsType = graphicsType;

	std::stringstream logMessage("[CoffeeEngineClass::InitializeGraphics] Attempting to create the graphics device ");
	logMessage << (graphicsType == GraphicsAPIType::DIRECTX ? "DirectX" : "OpenGL") << ".";
	m_pSystem->WriteToLog(logMessage);

	m_upGraphics = GraphicsFactory::CreateGraphics(graphicsType, m_pSystem);
	assert(m_upGraphics);
	if (m_upGraphics == nullptr)
		return false;

	//Parameterize the graphics settings into a structure to reduce the overhead produced by methods with an extremely long number of parameters.
	//NOTE: Temporary initialization...
	GRAPHICS_PRESENTATION_PROPERTIES graphicsInitParams;
	graphicsInitParams.fullscreen = false;
	graphicsInitParams.vsyncEnabled = true;
	graphicsInitParams.screenDepth = 1000.0f;
	graphicsInitParams.screenNear = 0.1f;
	graphicsInitParams.colorBits = 32;
	graphicsInitParams.depthBits = 32;
	graphicsInitParams.alphaBits = 8;
	graphicsInitParams.stencilBits = 8;
	graphicsInitParams.numberOfSamples = 1;
	graphicsInitParams.screenHeight = 480;
	graphicsInitParams.screenWidth = 640;
	graphicsInitParams.version.nMajor = 3;
	graphicsInitParams.version.nMinor = 1;

	//Initialize the graphics object first.
	if (!m_upGraphics->Initialize(graphicsInitParams))
		return false;

	m_pCamera = m_upGraphics->CreateCamera();
	m_pCamera->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	if (!m_pCamera->Initialize())
		return false;

	m_upGraphics->SetMasterCamera(m_pCamera);

	m_pShader = m_upGraphics->CreateShader();
	if (!m_pShader->Initialize("Default"))
		return false;

	m_pModel = m_upGraphics->CreateModel();
	if (!m_pModel->Initialize(m_pShader))
		return false;

	//Add our default shader just to rendering something.
	m_pModel->AddShader(m_pShader);

	m_pSystem->WriteToLog("[CoffeeEngineClass::InitializeGraphics] End", LogLevelType::Diagnostic);
	return true;
}

void CoffeeEngineClass::ShutdownGraphicsDisplay()
{
	m_pSystem->WriteToLog("[CoffeeEngineClass::ShutdownGraphicsDisplay] Begin", LogLevelType::Diagnostic);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pShader);
	m_pSystem->WriteToLog("[CoffeeEngineClass::ShutdownGraphicsDisplay] End", LogLevelType::Diagnostic);
}

////////////////////////////////////////////////////////////
//
//                Events
// 
////////////////////////////////////////////////////////////

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
		assert(m_pTimer);
		m_pTimer->Run();
		float elaspedTime = m_pTimer->GetElaspedTime();
		ManageWorld(elaspedTime);
		Render(elaspedTime);
	}
}

/// <summary>
/// This event is usually triggered when a keydown event occurs.
/// </summary>
void CoffeeEngineClass::OnKeyDown(KeyboardKeys keyboardKey)
{
	assert(m_pSystem);
	std::stringstream stream;
	stream << "[CoffeeEngineClass::OnKeyDown] Keycode: " << (int)keyboardKey;
	m_pSystem->WriteToLog(stream, LogLevelType::Diagnostic);

	if (keyboardKey == KeyboardKeys::LeftArrow)
	{
		m_turnMovement = -1.0f;
	}
	else if (keyboardKey == KeyboardKeys::RightArrow)
	{
		m_turnMovement = 1.0f;
	}

	if (keyboardKey == KeyboardKeys::UpArrow)
	{
		m_pitchMovement = -1.0f;
	}
	else if (keyboardKey == KeyboardKeys::DownArrow)
	{
		m_pitchMovement = 1.0f;
	}

	if (keyboardKey == KeyboardKeys::W)
	{
		m_forwardMovement = 1.0f;
	}
	else if (keyboardKey == KeyboardKeys::S)
	{
		m_forwardMovement = -1.0f;
	}
}

/// <summary>
/// This event is usually triggered when a keyup event occurs.
/// </summary>
void CoffeeEngineClass::OnKeyUp(KeyboardKeys keyboardKey)
{
	assert(m_pSystem);
	std::stringstream stream;
	stream << "[CoffeeEngineClass::OnKeyUp] Keycode: " << (int)keyboardKey;
	m_pSystem->WriteToLog(stream, LogLevelType::Diagnostic);

	if (keyboardKey == KeyboardKeys::Escape)
	{
		m_pSystem->Shutdown();
	}

	if (keyboardKey == KeyboardKeys::LeftArrow || keyboardKey == KeyboardKeys::RightArrow)
	{
		m_turnMovement = 0.0f;
	}

	if (keyboardKey == KeyboardKeys::UpArrow || keyboardKey == KeyboardKeys::DownArrow)
	{
		m_pitchMovement = 0.0f;
	}

	if (keyboardKey == KeyboardKeys::W || keyboardKey == KeyboardKeys::S)
	{
		m_forwardMovement = 0.0f;
	}
}

/// <summary>
/// This event is usually triggered when keyup and keydown are not handled.
/// </summary>
void CoffeeEngineClass::OnChar(uint characterCode)
{
	assert(m_pSystem);
	std::stringstream stream;
	stream << "[CoffeeEngineClass::OnChar] Keycode: " << characterCode;
	m_pSystem->WriteToLog(stream, LogLevelType::Diagnostic);
}

/// <summary>
/// This event is usually triggered when the graphis type has changed
/// </summary>
bool CoffeeEngineClass::OnGraphicsReset(GraphicsAPIType graphicsAPIType)
{
	assert(m_pSystem);
	m_pSystem->WriteToLog("[CoffeeEngineClass::OnGraphicsReset] Begin", LogLevelType::Diagnostic);

	//Prevent resetting the graphics display when unnecessary.
	if (m_graphicsType != graphicsAPIType)
	{
		m_pSystem->WriteToLog("[CoffeeEngineClass::OnGraphicsReset] Resetting...");
		ShutdownGraphicsDisplay();
		m_bReady = InitializeGraphics(graphicsAPIType);
	}

	m_pSystem->WriteToLog("[CoffeeEngineClass::OnGraphicsReset] End", LogLevelType::Diagnostic);
	return m_bReady;
}

/// <summary>
/// This event is usually triggered when a window is resized.
/// </summary>
void CoffeeEngineClass::OnWindowResize(int width, int height)
{
	assert(m_upGraphics);
	if (m_upGraphics != nullptr)
	{
		m_upGraphics.get()->SetScreenDimensions(width, height);
	}
}