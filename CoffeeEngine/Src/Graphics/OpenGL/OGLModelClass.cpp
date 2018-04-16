//--------------------------------------------------------------------------------------
// Description: The OpenGL model class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLCameraClass.hpp"
#include "OGLModelClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLModelClass::OGLModelClass(const BaseGraphicsClass* pBaseGraphicsClass)
	: ModelClass(pBaseGraphicsClass)
{

}

OGLModelClass::OGLModelClass(const OGLModelClass& object)
	: ModelClass(object)
{

}

OGLModelClass::~OGLModelClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool OGLModelClass::Initialize()
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLModelClass", "Initialize", "m_pGraphicsClass");

	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;

	std::string rootPath = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	std::string fileName = rootPath;
	
	fileName.append("/Media/coookeee.jpg");
	std::wstring fileNameW(fileName.begin(), fileName.end());
	
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

	return true;
}

void OGLModelClass::Render(IShader* pShader, float fElapsedTime)
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLModelClass", "Render", "m_pGraphicsClass");

	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;

	OGLCameraClass* pMasterCamera = (OGLCameraClass*)pGraphicsClass->GetMasterCamera();
	if(pMasterCamera == nullptr)
		throw Exception("OGLModelClass", "Render", "There is no master camera.  You need a camera to see!");

	//Render a shader if one was provided...if not good luck!
	if (pShader != nullptr)
		pShader->Render(fElapsedTime);

	//GL COMMENTED OUT FOR BUILD.
	//glLoadIdentity();
	//glTranslatef(0.0f, 0.0f, -10.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	//glVertex3f(-3.0f, 3.0f, 0.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glVertex3f(3.0f, 3.0f, 0.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glVertex3f(-3.0f, -3.0f, 0.0f);

	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glVertex3f(3.0f, 3.0f, 0.0f); 
	//glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
	//glVertex3f(3.0f, -3.0f, 0.0f); 
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glVertex3f(-3.0f, -3.0f, 0.0f); 
}

void OGLModelClass::Shutdown()
{
}

void OGLModelClass::Rotate(float x, float y, float z)
{
	//m_rotate = D3DXVECTOR3(x, y, z);
}

void OGLModelClass::Translate(float x, float y, float z)
{
	//m_translate = D3DXVECTOR3(x, y, z);
}

void OGLModelClass::Scale(float x, float y, float z)
{
	//m_scale = D3DXVECTOR3(x, y, z);
}