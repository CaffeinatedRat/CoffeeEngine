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
	// Initialize the world matrix to the identity matrix.
	m_worldMatrix = glm::mat4(1.0f);
}

OGLCameraClass::OGLCameraClass(const OGLCameraClass& object) noexcept
	: CameraClass(object),
	m_positionVector(object.m_positionVector)
{
}

OGLCameraClass::OGLCameraClass(OGLCameraClass&& object) noexcept
	: CameraClass(object),
	m_positionVector(std::move(object.m_positionVector))
{
	object.m_positionVector = glm::vec3();
	object.m_viewMatrix = glm::mat4();
	object.m_projectionMatrix = glm::mat4();
	object.m_worldMatrix = glm::mat4();
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
}

void OGLCameraClass::SetLookAt(Vector3&& vector)
{
	m_lookAt = std::move(vector);
}

/// <summary>
/// Sets the up vector of the camera.
/// </summary>
void OGLCameraClass::SetUp(const Vector3& vector)
{
	m_up = vector;
}

void OGLCameraClass::SetUp(Vector3&& vector)
{
	m_up = std::move(vector);
}

bool OGLCameraClass::Initialize()
{
	assert(m_pGraphicsClass);
	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Initialize] Begin");

	UpdateGraphicsProperties();

	m_positionVector = glm::ext::vec3(m_position);

	m_pGraphicsClass->GetSystem()->WriteToLog("[OGLCameraClass::Initialize] End");
	return true;
}

void OGLCameraClass::Render(float fElapsedTime)
{
	float velocity = CAMERA_SPEED * fElapsedTime;
	m_orientation._x += m_pitch * velocity;
	m_orientation._y += m_yaw * velocity;
	m_orientation._z += m_roll * velocity;

	auto rollMatrix = glm::rotate(glm::mat4(1.0f), m_orientation._z, glm::vec3(0.0f, 0.0f, 1.0f));
	auto pitchMatrix = glm::rotate(glm::mat4(1.0f), m_orientation._x, glm::vec3(1.0f, 0.0f, 0.0f));
	auto yawMatrix = glm::rotate(glm::mat4(1.0f), m_orientation._y, glm::vec3(0.0f, 1.0f, 0.0f));

	auto rotationMatrix = rollMatrix * pitchMatrix * yawMatrix;

	auto lookAt = glm::vec4(glm::ext::vec3(m_lookAt), 0.0f);
	auto lookAtVector = glm::vec3(glm::normalize(lookAt * rotationMatrix));

	auto upVector = glm::ext::vec3(m_up);
	m_viewMatrix = glm::lookAtRH(m_positionVector, (m_positionVector + lookAtVector), upVector);

	// ------------------------------------------------- //

	// Translate the rotated camera position to the location of the viewer.
	float forward = m_forward * velocity * 5.0f;
	m_positionVector += forward * lookAtVector;

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

	auto graphicsPresentation = m_pGraphicsClass->GetGraphicsPresentationProperties();

	assert(graphicsPresentation.screenHeight > 0);
	if (graphicsPresentation.screenHeight > 0)
	{
		// Setup the projection matrix.
		float fieldOfView = (graphicsPresentation.fov == 0.0f) ? Trig::C_QuarterPI : graphicsPresentation.fov;
		float screenAspect = graphicsPresentation.screenHeight > 0 ? ((float)graphicsPresentation.screenWidth / (float)graphicsPresentation.screenHeight) : 0.0f;

		// Create the projection matrix for 3D rendering.
		m_projectionMatrix = glm::perspective(fieldOfView, screenAspect, graphicsPresentation.screenNear, graphicsPresentation.screenDepth);
	}
}