//--------------------------------------------------------------------------------------
// Description: The OpenGL shader class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLShaderClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLShaderClass::OGLShaderClass(const BaseGraphicsClass* pBaseGraphicsClass)
	: ShaderClass(pBaseGraphicsClass)
{

}

OGLShaderClass::OGLShaderClass(const OGLShaderClass& object)
	: ShaderClass(object)
{
}

OGLShaderClass::~OGLShaderClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool OGLShaderClass::Initialize(const std::string& sFileName)
{
	if(sFileName.length() == 0)
		throw NullArgumentException("OGLShaderClass", "Initialize", "sFileName");

	//Post-Condition Note: This should never be null as only constructor requires this class to be passed as valid (non-null).
	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;

	// Compile the vertex shader code.
	std::string rootPath = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	std::string vertexShaderPath = rootPath;
	
	vertexShaderPath.append("/Shaders/DirectX11/");
	vertexShaderPath.append(sFileName);
	std::wstring vertexShaderPathW(vertexShaderPath.begin(), vertexShaderPath.end());

	return true;
}

bool OGLShaderClass::SetShaderParameters(float fElapsedTime)
{
	return true;
}

void OGLShaderClass::Render(float fElapsedTime)
{
	return;
}

void OGLShaderClass::Shutdown()
{
}