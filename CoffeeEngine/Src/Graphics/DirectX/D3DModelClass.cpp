//--------------------------------------------------------------------------------------
// Description: The D3D model class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#include "Common.hpp"
#include "D3DGraphicsClass.hpp"
#include "D3DModelClass.hpp"
#include "D3DShaderClass.hpp"
#include "WICTextureLoader.hpp"

#include <d3d11.h>
//#include <d3dx11async.h>

using namespace CoffeeEngine;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::DirectX;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

D3DModelClass::D3DModelClass(BaseGraphicsClass* pBaseGraphicsClass)
	: ModelClass(pBaseGraphicsClass)
{
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

bool D3DModelClass::Initialize(IShader* pShader)
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("D3DModelClass", "Initialize", "m_pGraphicsClass");

	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DModelClass::Initialize] Begin", LogLevelType::Diagnostic);

	auto pGraphicsClass = dynamic_cast<const D3DGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	//Locals
	bool bStatus = false;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	ID3D11Device* pDevice = pGraphicsClass->GetDevice();
	assert(pDevice);

	//Temporary...
	// Compile the vertex shader code.
	auto fileName = pGraphicsClass->GetSystem()->GetCurrentApplicationDirectory();
	
	fileName.append("/Media/coookeee.jpg");
	std::wstring fileNameW(fileName.begin(), fileName.end());

	HRESULT results = CreateWICTextureFromFile(pDevice, fileNameW.c_str(), nullptr, &m_pTexture);

	// Set the number of vertices in the vertex array.
	m_nVertexCount = 6;

	// Set the number of indices in the index array.
	m_nIndexCount = 6;

	// Create the vertex array.
	//auto vertices = std::unique_ptr<SimpleVertexType[]>(new SimpleVertexType[m_nVertexCount]);
	auto indices = std::unique_ptr<long[]>(new long[m_nVertexCount]);
	//SimpleVertexType* vertices = new SimpleVertexType[m_nIndexCount];
	//unsigned long* indices = new unsigned long[m_nIndexCount];
	
	//Temporary...
	//if ( (vertices != nullptr) && (indices != nullptr) )
	if ((indices != nullptr))
	{
		float vertices[] = {
			//positions           //RGBA                    //Textures
			-3.0f,  3.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
			3.0f,  3.0f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
			-3.0f, -3.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			3.0f, -3.0f, 0.0f,    1.0f, 0.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		};

		// Load the vertex array with data.
		//vertices[0].position = XMFLOAT3(-3.0f, 3.0f, 0.0f);  // Top left.
		//vertices[0].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
		//vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

		//vertices[1].position = XMFLOAT3(3.0f, 3.0f, 0.0f);  // Top right.
		//vertices[1].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		//vertices[1].texture = XMFLOAT2(1.0f, 0.0f);

		//vertices[2].position = XMFLOAT3(-3.0f, -3.0f, 0.0f);  // Bottom left.
		//vertices[2].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertices[2].texture = XMFLOAT2(0.0f, 1.0f);

		//vertices[3].position = XMFLOAT3(3.0f, -3.0f, 0.0f);  // Bottom Right.
		//vertices[3].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f);
		//vertices[3].texture = XMFLOAT2(1.0f, 1.0f);

		// Load the index array with data.
		indices[0] = 0;  // Top Left.
		indices[1] = 1;  // Top Right.
		indices[2] = 2;  // Bottom Left.
		indices[3] = 1;  // Top Right.
		indices[4] = 3;  // Bottom Right.
		indices[5] = 2;  // Bottom Right.

		// Set up the description of the vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = 9 * 4 * sizeof(float); //sizeof(SimpleVertexType) * m_nVertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now finally create the vertex buffer.
		if(SUCCEEDED(pDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer)))
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
		indexData.pSysMem = indices.get();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		if(SUCCEEDED(pDevice->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer)))
		{
			bStatus &= true;
		}
		else
		{
			bStatus &= false;
		}

		if (m_enableAlphaBlending) {
			ID3D11BlendState* d3dBlendState;
			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
			blendDesc.RenderTarget[0].BlendEnable = true;
			blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			if (SUCCEEDED(pDevice->CreateBlendState(&blendDesc, &d3dBlendState)))
			{
				pGraphicsClass->GetDeviceContext()->OMSetBlendState(d3dBlendState, 0, 0xffffffff);
				bStatus &= true;
			}
			else
			{
				bStatus &= false;
			}
		}
	}
	//END OF if ( (vertices != NULL) && (indices != NULL) )...
	
	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DModelClass::Initialize] End", LogLevelType::Diagnostic);

	return bStatus;
}

void D3DModelClass::Render(float fElapsedTime) const
{
	if(m_pGraphicsClass == nullptr)
		throw NullArgumentException("D3DModelClass", "Render", "m_pGraphicsClass");

	auto pGraphicsClass = dynamic_cast<const D3DGraphicsClass*>(m_pGraphicsClass);
	assert(pGraphicsClass);

	D3DCameraClass* pMasterCamera = (D3DCameraClass*)pGraphicsClass->GetMasterCamera();
	if(pMasterCamera == nullptr)
		throw Exception("D3DModelClass", "Render", "There is no master camera.  You need a camera to see!");

	//Apply transformations.
	XMMATRIX worldMatrix = pMasterCamera->GetWorldMatrix();
	XMMATRIX scaleMatrix, translateMatrix, rotateMatrix;

	//NOTE: The order of Matrix transformations matter and will result in different effects.
	// This simple transformation does not take into account more complex transformations.
	scaleMatrix = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	worldMatrix *= scaleMatrix;
	rotateMatrix = XMMatrixRotationRollPitchYaw(m_rotate.y, m_rotate.x, m_rotate.z);
	worldMatrix *= rotateMatrix;
	translateMatrix = XMMatrixTranslation(m_translate.x, m_translate.y, m_translate.z);
	worldMatrix *= translateMatrix;

	//Get the shaders.
	auto firstShader = (CoffeeEngine::Graphics::DirectX::D3DShaderClass*)(m_shaders.size() > 0 ? m_shaders[0] : nullptr);
	if (firstShader != nullptr) {
		firstShader->SetWorldMatrix(worldMatrix);
	}

	//Render all shaders.
	if (m_shaders.size() > 1)
	{
		//TODO: Make it dynamic cast, but it requires changing render to be a const function.
		firstShader->Render(fElapsedTime);
	}
	else
	{
		//TODO: Make it dynamic cast, but it requires changing render to be a const function.
		for (const IShader* pShader : m_shaders) {
			CoffeeEngine::Graphics::DirectX::D3DShaderClass* shader = (CoffeeEngine::Graphics::DirectX::D3DShaderClass*)pShader;
			if (shader != nullptr) {
				shader->Render(fElapsedTime);
			}
		}
	}

	// Set vertex buffer stride and offset.
	//unsigned int stride = sizeof(SimpleVertexType); 
	unsigned int stride = (sizeof(float) * 3) + (sizeof(float) * 4) + (sizeof(float) * 2);
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
	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DModelClass::Shutdown] Begin", LogLevelType::Diagnostic);

	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);

	//Temporary
	SAFE_RELEASE(m_pTexture);

	m_nVertexCount = 0;
	m_nIndexCount = 0;
	m_pGraphicsClass->GetSystem()->WriteToLog("[D3DModelClass::Shutdown] End", LogLevelType::Diagnostic);
}

void D3DModelClass::Rotate(float x, float y, float z)
{
	m_rotate = XMFLOAT3(x, y, z);
}

void D3DModelClass::Translate(float x, float y, float z)
{
	m_translate = XMFLOAT3(x, y, z);
}

void D3DModelClass::Scale(float x, float y, float z)
{
	m_scale = XMFLOAT3(x, y, z);
}

#endif