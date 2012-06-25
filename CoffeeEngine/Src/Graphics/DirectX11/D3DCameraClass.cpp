//--------------------------------------------------------------------------------------
// Description: The D3D camera class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#include "Graphics\DirectX11\D3DGraphicsClass.h"
#include "Graphics\DirectX11\D3DCameraClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::DirectX11;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

D3DCameraClass::D3DCameraClass(BaseGraphicsClass* pBaseGraphicsClass)
	: CameraClass(pBaseGraphicsClass)
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
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
	if(m_pGraphicsClass == NULL)
		throw NullArgumentException("D3DCameraClass", "Initialize", "m_pGraphicsClass");

	D3DGraphicsClass* pGraphicsClass = (D3DGraphicsClass*)m_pGraphicsClass;

	int nScreenWidth, nScreenHeight;
	pGraphicsClass->GetScreenProperties(nScreenWidth, nScreenHeight);

	float screenDepth = 1000.0f;
	float screenNear = 0.1f;

	// Setup the projection matrix.
	float fieldOfView = (float)D3DX_PI / 4.0f;
	float screenAspect = (float)nScreenWidth / (float)nScreenHeight;

	// Create the projection matrix for 3D rendering.
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	// Initialize the world matrix to the identity matrix.
	D3DXMatrixIdentity(&m_worldMatrix);

	return true;
}

void D3DCameraClass::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = -10.0f;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}

void D3DCameraClass::Shutdown()
{

}