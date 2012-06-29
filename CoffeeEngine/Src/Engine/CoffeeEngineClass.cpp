//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Engine\CoffeeEngineClass.h"

#include "Global.h"
#include "Interfaces\ISystem.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\ModelClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Engine;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

CoffeeEngineClass::CoffeeEngineClass()
{
	m_pSystem = NULL;
	m_pTimer = NULL;

	m_pGraphics = NULL;
	m_pCamera = NULL;
	m_pModel = NULL;
	m_pShader = NULL;

	m_bReady = false;
}

CoffeeEngineClass::CoffeeEngineClass(ISystem* pSystem, BaseGraphicsClass* pGraphics)
{
	if(pSystem == NULL)
		throw NullArgumentException("CoffeeEngineClass", "Constructor", "pSystem");

	if(pGraphics == NULL)
		throw NullArgumentException("CoffeeEngineClass", "Constructor", "pGraphics");

	m_pSystem = pSystem;
	m_pTimer = NULL;
	
	m_pGraphics = pGraphics;
	m_pCamera = NULL;
	m_pModel = NULL;
	m_pShader = NULL;

	m_bReady = false;
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
	if(m_pSystem == NULL)
		throw NullArgumentException("CoffeeEngineClass", "Initialize", "m_pSystem");

	if(m_pGraphics == NULL)
		throw NullArgumentException("CoffeeEngineClass", "Initialize", "m_pGraphics");

	//Create the system timer.
	m_pTimer = m_pSystem->CreateTimer();
	if(!m_pTimer->Start())
		return false;

	m_pCamera = m_pGraphics->CreateCamera();
	if(!m_pCamera->Initialize())
		return false;

	m_pGraphics->SetMasterCamera(m_pCamera);

	m_pModel = m_pGraphics->CreateModel();
	if(!m_pModel->Initialize())
		return false;

	m_pShader = m_pGraphics->CreateShader();
	if(!m_pShader->Initialize("Default.fx"))
		return false;

	return (m_bReady = true);
}

void CoffeeEngineClass::Run()
{
	if(m_bReady)
	{
		m_pTimer->Run();
		this->Render();
	}
}

void CoffeeEngineClass::Render()
{
	static float rotationY = 0.0f;
	static float rotationX = 0.0f;
	static float rotationZ = 0.0f;

	m_pGraphics->BeginScene(0.0f, 0.3f, 0.7f, 0.5f);

	m_pCamera->Render(m_pTimer->GetElaspedTime());

	//m_pModel->Scale(0.5f, 2.0f, 1.0f);
	m_pModel->Rotate(rotationX, rotationY, rotationZ);
	m_pModel->Translate(-1.0f, 1.0f, 5.0f);
	m_pModel->Render(m_pShader, m_pTimer->GetElaspedTime());

	rotationY += 0.005f;
	rotationX += 0.01f;
	rotationZ += 0.01f;

	m_pGraphics->EndScene();
}

bool CoffeeEngineClass::Frame()
{
	this->Render();
	return true;
}

void CoffeeEngineClass::Shutdown()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pTimer);

	m_bReady = false;
}