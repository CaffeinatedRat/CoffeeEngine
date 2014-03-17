//--------------------------------------------------------------------------------------
// Description: The D3D model class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Graphics/DirectX11/D3DGraphicsClass.h"
#include "Graphics/DirectX11/D3DModelClass.h"

#include "Graphics/DirectX11/D3DShaderClass.h"

#include <d3d11.h>
#include <d3dx11async.h>

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::DirectX11;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

D3DModelClass::D3DModelClass(BaseGraphicsClass* pBaseGraphicsClass)
	: ModelClass(pBaseGraphicsClass)
{
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;

	//Temporary
	m_pTexture = NULL;

	m_rotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_translate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

D3DModelClass::D3DModelClass(const D3DModelClass& object)
	: ModelClass(object)
{
	//m_pShader = object.m_pShader;
}

D3DModelClass::~D3DModelClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool D3DModelClass::Initialize()
{
	if(m_pGraphicsClass == NULL)
		throw NullArgumentException("D3DModelClass", "Initialize", "m_pGraphicsClass");

	D3DGraphicsClass* pGraphicsClass = (D3DGraphicsClass*)m_pGraphicsClass;

	//Locals
	bool bStatus = false;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	ID3D11Device* pDevice = pGraphicsClass->GetDevice();

	//Temporary...
	// Compile the vertex shader code.
	std::string rootPath = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	std::string fileName = rootPath;
	
	fileName.append("/Media/coookeee.jpg");
	std::wstring fileNameW(fileName.begin(), fileName.end());

	D3DX11CreateShaderResourceViewFromFile(pDevice, fileNameW.c_str(), NULL, NULL, &m_pTexture, NULL);

	// Set the number of vertices in the vertex array.
	m_nVertexCount = 6;

	// Set the number of indices in the index array.
	m_nIndexCount = 6;

	// Create the vertex array.
	SimpleVertexType* vertices = new SimpleVertexType[m_nVertexCount];
	unsigned long* indices = new unsigned long[m_nIndexCount];
	
	//Temporary...
	if ( (vertices != NULL) && (indices != NULL) ) 
	{
		// Load the vertex array with data.
		vertices[0].position = D3DXVECTOR3(-3.0f, 3.0f, 0.0f);  // Top left.
		vertices[0].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f);
		vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

		vertices[1].position = D3DXVECTOR3(3.0f, 3.0f, 0.0f);  // Top right.
		vertices[1].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[1].texture = D3DXVECTOR2(1.0f, 0.0f);

		vertices[2].position = D3DXVECTOR3(-3.0f, -3.0f, 0.0f);  // Bottom left.
		vertices[2].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

		vertices[3].position = D3DXVECTOR3(3.0f, 3.0f, 0.0f);  // Top right.
		vertices[3].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[3].texture = D3DXVECTOR2(1.0f, 0.0f);

		vertices[4].position = D3DXVECTOR3(3.0f, -3.0f, 0.0f);  // Bottom Right.
		vertices[4].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.2f);
		vertices[4].texture = D3DXVECTOR2(1.0f, 1.0f);

		vertices[5].position = D3DXVECTOR3(-3.0f, -3.0f, 0.0f);  // Bottom left.
		vertices[5].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertices[5].texture = D3DXVECTOR2(0.0f, 1.0f);

		// Load the index array with data.
		indices[0] = 0;  // Top Left.
		indices[1] = 1;  // Top Right.
		indices[2] = 2;  // Bottom Left.
		indices[3] = 3;  // Bottom Right.
		indices[4] = 4;  // Bottom Right.
		indices[5] = 5;  // Bottom Right.

		// Set up the description of the vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(SimpleVertexType) * m_nVertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now finally create the vertex buffer.
		if(SUCCEEDED(pGraphicsClass->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer)))
		{
			bStatus = true;
		}

		// Set up the description of the index buffer.
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_nIndexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the index data.
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		if(SUCCEEDED(pGraphicsClass->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer)))
		{
			bStatus &= true;
		}
		else
		{
			bStatus &= false;
		}
	}
	//END OF if ( (vertices != NULL) && (indices != NULL) )...

	// Clean up regardless of the status.
	SAFE_ARRAY_DELETE(vertices);
	SAFE_ARRAY_DELETE(indices);
	
	return bStatus;
}

void D3DModelClass::Render(IShader* pShader, float fElapsedTime)
{
	if(m_pGraphicsClass == NULL)
		throw NullArgumentException("D3DModelClass", "Render", "m_pGraphicsClass");

	D3DGraphicsClass* pGraphicsClass = (D3DGraphicsClass*)m_pGraphicsClass;

	D3DCameraClass* pMasterCamera = (D3DCameraClass*)pGraphicsClass->GetMasterCamera();
	if(pMasterCamera == NULL)
		throw Exception("D3DModelClass", "Render", "There is no master camera.  You need a camera to see!");

	//Apply transformations.
	D3DXMATRIX worldMatrix = pMasterCamera->GetWorldMatrix();
	D3DXMATRIX scaleMatrix, translateMatrix, rotateMatrix;

	//NOTE: The order of Matrix transformations matter and will result in different effects.
	// This simple transformation does not take into account more complex transformations.
	D3DXMatrixScaling(&scaleMatrix, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scaleMatrix);
	D3DXMatrixRotationYawPitchRoll(&rotateMatrix, m_rotate.y, m_rotate.x, m_rotate.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotateMatrix);
	D3DXMatrixTranslation(&translateMatrix, m_translate.x, m_translate.y, m_translate.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	((CoffeeEngine::Graphics::DirectX11::D3DShaderClass*)pShader)->SetWorldMatrix(worldMatrix);

	//Render a shader if one was provided...if not good luck!
	if (pShader != NULL)
		pShader->Render(fElapsedTime);
	
	// Set vertex buffer stride and offset.
	unsigned int stride = sizeof(SimpleVertexType); 
	unsigned int offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pGraphicsClass->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pGraphicsClass->GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pGraphicsClass->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Render the texture.
	pGraphicsClass->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);

	// Render the triangle.
	pGraphicsClass->GetDeviceContext()->DrawIndexed(m_nIndexCount, 0, 0);
}

void D3DModelClass::Shutdown()
{
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);

	//Temporary
	SAFE_RELEASE(m_pTexture);

	m_nVertexCount = 0;
	m_nIndexCount = 0;
}

void D3DModelClass::Rotate(float x, float y, float z)
{
	m_rotate = D3DXVECTOR3(x, y, z);
}

void D3DModelClass::Translate(float x, float y, float z)
{
	m_translate = D3DXVECTOR3(x, y, z);
}

void D3DModelClass::Scale(float x, float y, float z)
{
	m_scale = D3DXVECTOR3(x, y, z);
}