//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
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
	m_pGraphics = NULL;

	m_pCamera = NULL;
	m_pModel = NULL;
	m_pShader = NULL;
}

CoffeeEngineClass::CoffeeEngineClass(ISystem* pSystem, BaseGraphicsClass* pGraphics)
{
	if(pSystem == NULL)
		throw NullArgumentException("CoffeeEngineClass", "Constructor", "pSystem");

	if(pGraphics == NULL)
		throw NullArgumentException("CoffeeEngineClass", "Constructor", "pGraphics");

	m_pSystem = pSystem;
	m_pGraphics = pGraphics;

	m_pSystem->ConsoleWrite("Constructing!");

	m_pCamera = NULL;
	m_pModel = NULL;
	m_pShader = NULL;
}

CoffeeEngineClass::~CoffeeEngineClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public
// 
////////////////////////////////////////////////////////////

bool CoffeeEngineClass::Initialize()
{
	m_pSystem->ConsoleWrite("Initializing!");

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

	return true;
}

void CoffeeEngineClass::Run()
{
	this->Render();
}

void CoffeeEngineClass::Render()
{
	m_pGraphics->BeginScene(0.0f, 0.3f, 0.7f, 0.5f);

	m_pCamera->Render();
	m_pModel->Render(m_pShader);

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
}