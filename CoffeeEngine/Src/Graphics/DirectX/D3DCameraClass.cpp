//--------------------------------------------------------------------------------------
// Description: The D3D camera class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#include "Common.hpp"
#include "D3DGraphicsClass.hpp"
#include "D3DCameraClass.hpp"

#include <cmath>

//using namespace DirectX11;

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::DirectX;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

D3DCameraClass::D3DCameraClass(const BaseGraphicsClass* pBaseGraphicsClass)
	: CameraClass(pBaseGraphicsClass)
{
	// Initialize the world matrix to the identity matrix.
	m_worldMatrix = XMMatrixIdentity();
}

D3DCameraClass::D3DCameraClass(const D3DCameraClass& object) noexcept
	: CameraClass(object),
	m_positionVector(m_positionVector),
	m_lookAtVector(m_lookAtVector),
	m_upVector(m_upVector)
{
}

D3DCameraClass::D3DCameraClass(D3DCameraClass&& object) noexcept
	: CameraClass(object),
	m_positionVector(std::move(object.m_positionVector)),
	m_lookAtVector(std::move(object.m_lookAtVector)),
	m_upVector(std::move(object.m_upVector))
{
	object.m_positionVector = XMVECTOR();
	object.m_lookAtVector = XMVECTOR();
	object.m_upVector = XMVECTOR();
	object.m_viewMatrix = XMMATRIX();
	object.m_projectionMatrix = XMMATRIX();
	object.m_worldMatrix = XMMATRIX();
}

D3DCameraClass::~D3DCameraClass()
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
void D3DCameraClass::SetPosition(const Vector3& vector)
{
	m_position = vector;

	// Setup the position of the camera in the world.
	XMFLOAT3 position = { m_position._x, m_position._y, m_position._z};
	m_positionVector = XMLoadFloat3(&position);
}

void D3DCameraClass::SetPosition(Vector3&& vector)
{
	m_position = std::move(vector);

	// Setup the position of the camera in the world.
	XMFLOAT3 position = { m_position._x, m_position._y, m_position._z };
	m_positionVector = XMLoadFloat3(&position);
}

/// <summary>
/// Sets the lookat vector of the camera.
/// </summary>
void D3DCameraClass::SetLookAt(const Vector3& vector)
{
	m_lookAt = vector;

	XMFLOAT3 lookAt = { m_lookAt._x, m_lookAt._y, m_lookAt._z };
	m_lookAtVector = XMLoadFloat3(&lookAt);
}

void D3DCameraClass::SetLookAt(Vector3&& vector)
{
	m_lookAt = std::move(vector);

	XMFLOAT3 lookAt = { m_lookAt._x, m_lookAt._y, m_lookAt._z };
	m_lookAtVector = XMLoadFloat3(&lookAt);
}

/// <summary>
/// Sets the up vector of the camera.
/// </summary>
void D3DCameraClass::SetUp(const Vector3& vector)
{
	m_up = vector;

	XMFLOAT3 up = { m_up._x, m_up._y, m_up._z };
	m_upVector = XMLoadFloat3(&up);
}

void D3DCameraClass::SetUp(Vector3&& vector)
{
	m_up = std::move(vector);

	XMFLOAT3 up = { m_up._x, m_up._y, m_up._z };
	m_upVector = XMLoadFloat3(&up);
}

bool D3DCameraClass::Initialize()
{
	assert(m_pGraphicsClass);
	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DCameraClass::Initialize] Begin");

	UpdateGraphicsProperties();

	// Set the initial position vector.
	XMFLOAT3 position = { m_position._x, m_position._y, m_position._z };
	m_positionVector = XMLoadFloat3(&position);

	// Set the initial lookat vector.
	XMFLOAT3 lookAt = { m_lookAt._x, m_lookAt._y, m_lookAt._z };
	m_lookAtVector = XMLoadFloat3(&lookAt);

	// Set the initial up vector.
	XMFLOAT3 up = { m_up._x, m_up._y, m_up._z };
	m_upVector = XMLoadFloat3(&up);

	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DCameraClass::Initialize] End");
	return true;
}

void D3DCameraClass::Render(float fElapsedTime)
{
	float yawRate = m_yaw * 0.001f * fElapsedTime;
	float rollRate = m_roll * 0.001f * fElapsedTime;
	float pitchRate = m_pitch * 0.001f * fElapsedTime;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	auto rotationMatrix = XMMatrixRotationRollPitchYaw(pitchRate, yawRate, rollRate);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	m_lookAtVector = XMVector3Normalize(XMVector3TransformCoord(m_lookAtVector, rotationMatrix));

	// Translate the rotated camera position to the location of the viewer.
	m_positionVector += m_forward * m_lookAtVector;

	//auto upVector = XMVector3TransformCoord(m_upVector, rotationMatrix);
	auto upVector = m_upVector;

	// --- KDA (8/13/18) --- Switch to a right-handed coordinate system to make it easier to sync with OpenGL.
	// Finally create the view matrix from the three updated vectors.
	//m_viewMatrix = XMMatrixLookAtLH(m_positionVector, m_lookAtVector + m_positionVector, upVector);
	m_viewMatrix = XMMatrixLookAtRH(m_positionVector, m_lookAtVector + m_positionVector, upVector);

	return;
}

void D3DCameraClass::Shutdown()
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DCameraClass::Shutdown] Shutting down...");
}

/// <summary>
/// Updates the graphics properties such as aspect ratio and fov.
/// </summary>
void D3DCameraClass::UpdateGraphicsProperties()
{
	auto pGraphicsClass = dynamic_cast<const D3DGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	auto graphicsPresentation = pGraphicsClass->GetGraphicsPresentationProperties();

	// Setup the projection matrix.
	float fieldOfView = (graphicsPresentation.fov == 0.0f) ? ((float)XM_PI / 4.0f) : graphicsPresentation.fov;
	float screenAspect = (float)graphicsPresentation.screenWidth / (float)graphicsPresentation.screenHeight;

	// --- KDA (8/13/18) --- Switch to a right-handed coordinate system to make it easier to sync with OpenGL.
	// Create the projection matrix for 3D rendering.
	//m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, graphicsPresentation.screenNear, graphicsPresentation.screenDepth);
	m_projectionMatrix = XMMatrixPerspectiveFovRH(fieldOfView, screenAspect, graphicsPresentation.screenNear, graphicsPresentation.screenDepth);
}

#endif