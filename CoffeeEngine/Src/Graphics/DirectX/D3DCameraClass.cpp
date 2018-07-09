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
}

D3DCameraClass::D3DCameraClass(const D3DCameraClass& object)
	: CameraClass(object)
{
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

bool D3DCameraClass::Initialize()
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("D3DCameraClass", "Initialize", "m_pGraphicsClass");

	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DCameraClass::Initialize] Beginning...");

	D3DGraphicsClass* pGraphicsClass = (D3DGraphicsClass*)m_pGraphicsClass;

	int nScreenWidth, nScreenHeight;
	pGraphicsClass->GetScreenProperties(nScreenWidth, nScreenHeight);

	float screenDepth = 1000.0f;
	float screenNear = 0.1f;

	// Setup the projection matrix.
	float fieldOfView = (float)XM_PI / 4.0f;
	float screenAspect = (float)nScreenWidth / (float)nScreenHeight;

	// Create the projection matrix for 3D rendering.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	// Initialize the world matrix to the identity matrix.
	m_worldMatrix = XMMatrixIdentity();

	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DCameraClass::Initialize] Completed.");

	return true;
}

void D3DCameraClass::Render(float fElapsedTime)
{
	XMFLOAT3 up, position, lookAt;
	float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	XMVECTOR upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = -10.0f;

	XMVECTOR positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	XMVECTOR lookAtVector = XMLoadFloat3(&lookAt);

	//m_rotationX = fmod((m_rotationX + 0.001f * fElapsedTime),3.14f);
	//m_rotationY = fmod((m_rotationY + 0.001f * fElapsedTime),3.14f);
	//m_rotationZ = fmod((m_rotationZ + 0.001f * fElapsedTime),3.14f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	//pitch = m_rotationX;// * 0.0174532925f * fElapsedTime;
	//yaw   = m_rotationY;// * 0.0174532925f * fElapsedTime;
	//roll  = m_rotationZ;// * 0.0174532925f * fElapsedTime;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

void D3DCameraClass::Shutdown()
{
	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DCameraClass::Shutdown] Shutting down...");
}

#endif