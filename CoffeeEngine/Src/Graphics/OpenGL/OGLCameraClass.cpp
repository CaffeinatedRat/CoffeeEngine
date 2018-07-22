//--------------------------------------------------------------------------------------
// Description: The OpenGL camera class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "OGLGraphicsClass.hpp"
#include "OGLCameraClass.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

OGLCameraClass::OGLCameraClass(const OGLCameraClass& object) noexcept
	: CameraClass(object),
	m_positionVector(object.m_positionVector),
	m_lookAtVector(object.m_lookAtVector),
	m_upVector(object.m_upVector),
	m_viewMatrix(object.m_viewMatrix),
	m_projectionMatrix(object.m_projectionMatrix),
	m_worldMatrix(object.m_worldMatrix),
	m_positionX(object.m_positionX),
	m_positionY(object.m_positionY),
	m_positionZ(object.m_positionZ),
	m_rotationX(object.m_rotationX),
	m_rotationY(object.m_rotationY),
	m_rotationZ(object.m_rotationZ)
{
}

OGLCameraClass::OGLCameraClass(OGLCameraClass&& object) noexcept
	: CameraClass(object),
	m_positionVector(std::move(object.m_positionVector)),
	m_lookAtVector(std::move(object.m_lookAtVector)),
	m_upVector(std::move(object.m_upVector)),
	m_viewMatrix(std::move(object.m_viewMatrix)),
	m_projectionMatrix(std::move(object.m_projectionMatrix)),
	m_worldMatrix(std::move(object.m_worldMatrix)),
	m_positionX(object.m_positionX),
	m_positionY(object.m_positionY),
	m_positionZ(object.m_positionZ),
	m_rotationX(object.m_rotationX),
	m_rotationY(object.m_rotationY),
	m_rotationZ(object.m_rotationZ)
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

/// <summary>
/// Sets the vector position of the camera.
/// </summary>
void OGLCameraClass::SetPosition(const Vector3& vector)
{
	m_position = vector;
	m_positionVector = glm::ext::vec3(m_position);
}

void OGLCameraClass::SetPosition(Vector3&& vector)
{
	m_position = std::move(vector);
	m_positionVector = glm::ext::vec3(m_position);
}

/// <summary>
/// Sets the lookat vector of the camera.
/// </summary>
void OGLCameraClass::SetLookAt(const Vector3& vector)
{
	m_lookAt = vector;
	m_lookAtVector = glm::ext::vec3(m_lookAt);
}

void OGLCameraClass::SetLookAt(Vector3&& vector)
{
	m_lookAt = std::move(vector);
	m_lookAtVector = glm::ext::vec3(m_lookAt);
}

/// <summary>
/// Sets the up vector of the camera.
/// </summary>
void OGLCameraClass::SetUp(const Vector3& vector)
{
	m_up = vector;
	m_upVector = glm::ext::vec3(m_up);
}

void OGLCameraClass::SetUp(Vector3&& vector)
{
	m_up = std::move(vector);
	m_upVector = glm::ext::vec3(m_up);
}

bool OGLCameraClass::Initialize()
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("OGLCameraClass", "Initialize", "m_pGraphicsClass");

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Initialize] Beginning...");

	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;
	assert(pGraphicsClass);

	int nScreenWidth, nScreenHeight;
	pGraphicsClass->GetScreenProperties(nScreenWidth, nScreenHeight);

	float screenDepth = 1000.0f;
	float screenNear = 0.1f;

	// Setup the projection matrix.
	float fieldOfView = (float)OGL_PI / 4.0f;
	float screenAspect = (float)nScreenWidth / (float)nScreenHeight;

	// Create the projection matrix for 3D rendering.
	m_projectionMatrix = glm::perspective(fieldOfView, screenAspect, screenNear, screenDepth);

	//glMatrixTranslatefEXT();

	m_positionVector = glm::ext::vec3(m_position);
	m_lookAtVector = glm::ext::vec3(m_lookAt);
	m_upVector = glm::ext::vec3(m_up);

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Initialize] Completed.");
	return true;
}

void OGLCameraClass::Render(float fElapsedTime)
{
	float yawRate = m_yaw * 0.001f * fElapsedTime;
	float rollRate = m_roll * 0.001f * fElapsedTime;
	float pitchRate = m_pitch * 0.001f * fElapsedTime;

	glm::vec3 front = m_lookAtVector;
	//front.x += cos(yawRate) * cos(pitchRate);
	//front.y += sin(pitchRate);
	//front.z += sin(yawRate) * cos(pitchRate);

	//m_lookAtVector = front = glm::normalize(front);
	
	// Translate the rotated camera position to the location of the viewer.
	m_positionVector += m_forward * m_lookAtVector;

	// Also re-calculate the Right and Up vector
	auto Right = glm::normalize(glm::cross(front, m_upVector));
	auto upVector = glm::normalize(glm::cross(Right, front));

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = glm::lookAt(m_positionVector, (m_lookAtVector + m_positionVector), upVector);
	return;
}

void OGLCameraClass::Shutdown()
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Shutdown] Shutting down...");
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