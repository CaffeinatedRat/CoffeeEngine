//--------------------------------------------------------------------------------------
// Description: The OpenGL camera class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "Graphics/OpenGL/OGLGraphicsClass.hpp"
#include "Graphics/OpenGL/OGLCameraClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLCameraClass::OGLCameraClass(const BaseGraphicsClass* pBaseGraphicsClass)
	: CameraClass(pBaseGraphicsClass)
{
}

OGLCameraClass::OGLCameraClass(const OGLCameraClass& object)
	: CameraClass(object)
{
}

OGLCameraClass::~OGLCameraClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool OGLCameraClass::Initialize()
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLCameraClass", "Initialize", "m_pGraphicsClass");

	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;

	int nScreenWidth, nScreenHeight;
	pGraphicsClass->GetScreenProperties(nScreenWidth, nScreenHeight);

	//GL COMMENTED OUT FOR BUILD.
	//glMatrixMode(GL_PROJECTION); 
	//glLoadIdentity();

	float screenDepth = 1000.0f;
	float screenNear = 0.1f;

	// Setup the projection matrix.
	float fieldOfView = (float)OGL_PI / 4.0f;
	float screenAspect = (float)nScreenWidth / (float)nScreenHeight;

	//GL COMMENTED OUT FOR BUILD.
	// Create the projection matrix for 3D rendering.
	//glm::mat4 Projection = glm::perspective(fieldOfView, screenAspect, screenNear, screenDepth);

	//GL COMMENTED OUT FOR BUILD.
	// Initialize the world matrix to the identity matrix.
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	return true;
}

void OGLCameraClass::Render(float fElapsedTime)
{
	//GL COMMENTED OUT FOR BUILD.
	//glLoadIdentity();
	return;
}

void OGLCameraClass::Shutdown()
{

}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////
void OGLCameraClass::OGLMatrixPerspectiveFovLH(float *m, float fov, float aspect, float znear, float zfar)
{
	float ymax = znear * tan(fov * OGL_PI / 180);
	float ymin = -ymax;
	float xmax = ymax * aspect;
	float xmin = ymin * aspect;

	float width = xmax - xmin;
	float height = ymax - ymin;

	float depth = zfar - znear;
	float q = -(zfar + znear) / depth;
	float qn = -2 * (zfar * znear) / depth;

	float w = 2 * znear / width;
	w = w / aspect;
	float h = 2 * znear / height;

	m[0]  = w;
	m[1]  = 0;
	m[2]  = 0;
	m[3]  = 0;

	m[4]  = 0;
	m[5]  = h;
	m[6]  = 0;
	m[7]  = 0;

	m[8]  = 0;
	m[9]  = 0;
	m[10] = q;
	m[11] = -1;
}