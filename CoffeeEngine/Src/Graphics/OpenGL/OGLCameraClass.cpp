//--------------------------------------------------------------------------------------
// Description: The OpenGL camera class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Graphics\OpenGL\OGLGraphicsClass.h"
#include "Graphics\OpenGL\OGLCameraClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::OpenGL;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

OGLCameraClass::OGLCameraClass(BaseGraphicsClass* pBaseGraphicsClass)
	: CameraClass(pBaseGraphicsClass)
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
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
	if(m_pGraphicsClass == NULL)
		throw NullArgumentException("OGLCameraClass", "Initialize", "m_pGraphicsClass");

	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;

	int nScreenWidth, nScreenHeight;
	pGraphicsClass->GetScreenProperties(nScreenWidth, nScreenHeight);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	float screenDepth = 1000.0f;
	float screenNear = 0.1f;

	// Setup the projection matrix.
	float fieldOfView = (float)OGL_PI / 4.0f;
	float screenAspect = (float)nScreenWidth / (float)nScreenHeight;

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(fieldOfView, screenAspect, screenNear, screenDepth);

	// Initialize the world matrix to the identity matrix.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return true;
}

void OGLCameraClass::Render(float fElapsedTime)
{
	glLoadIdentity();
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