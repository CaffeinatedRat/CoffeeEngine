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
	object.m_positionVector = glm::vec3();
	object.m_lookAtVector = glm::vec3();
	object.m_upVector = glm::vec3();
	object.m_viewMatrix = glm::mat4();
	object.m_projectionMatrix = glm::mat4();
	object.m_worldMatrix = glm::mat4();
	object.m_positionX = object.m_positionY = object.m_positionZ = 0.0f;
	object.m_rotationX = object.m_rotationY = object.m_rotationZ = 0.0f;
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
	assert(m_pGraphicsClass);
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Initialize] Begin");

	UpdateGraphicsProperties();

	m_positionVector = glm::ext::vec3(m_position);
	m_lookAtVector = glm::ext::vec3(m_lookAt);
	m_upVector = glm::ext::vec3(m_up);

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Initialize] End");
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

/// <summary>
/// Updates the graphics properties such as aspect ratio and fov.
/// </summary>
void OGLCameraClass::UpdateGraphicsProperties()
{
	assert(m_pGraphicsClass);
	
	OGLGraphicsClass* pGraphicsClass = (OGLGraphicsClass*)m_pGraphicsClass;
	assert(pGraphicsClass);

	auto graphicsPresentation = pGraphicsClass->GetGraphicsPresentationProperties();

	// Setup the projection matrix.
	float fieldOfView = (graphicsPresentation.fov == 0.0f) ? ((float)OGL_PI / 4.0f) : graphicsPresentation.fov;
	float screenAspect = (float)graphicsPresentation.screenWidth / (float)graphicsPresentation.screenHeight;

	// Create the projection matrix for 3D rendering.
	m_projectionMatrix = glm::perspective(fieldOfView, screenAspect, graphicsPresentation.screenNear, graphicsPresentation.screenDepth);
}