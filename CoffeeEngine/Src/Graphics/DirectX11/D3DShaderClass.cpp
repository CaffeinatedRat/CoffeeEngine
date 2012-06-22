//--------------------------------------------------------------------------------------
// Description: The D3D shader class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#include "Graphics\DirectX11\D3DGraphicsClass.h"
#include "Graphics\DirectX11\D3DShaderClass.h"

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

D3DShaderClass::D3DShaderClass(BaseGraphicsClass* pBaseGraphicsClass)
	: ShaderClass(pBaseGraphicsClass)
{
	m_pVertexShader = NULL;
	m_pPixelShader = NULL;

	m_pLayout = NULL;
	m_pMatrixBuffer = NULL;
	m_pSampleState = NULL;
}

D3DShaderClass::D3DShaderClass(const D3DShaderClass& object)
	: ShaderClass(object)
{
}

D3DShaderClass::~D3DShaderClass()
{
	Shutdown();
}

bool D3DShaderClass::Initialize(std::string sFileName)
{
	if(sFileName.length() == 0)
		throw NullArgumentException("D3DShaderClass", "Initialize", "sFileName");

	D3DGraphicsClass* pGraphicsClass = (D3DGraphicsClass*)m_pGraphicsClass;

	//Locals
	bool bStatus = false;
	HRESULT result;
	ID3D10Blob* pErrorMessage = NULL;
	ID3D10Blob* pVertexShaderBuffer = NULL;
	ID3D10Blob* pPixelShaderBuffer = NULL;

	// Compile the vertex shader code.
	std::string rootPath = pGraphicsClass->GetSystem()->GetCurrentDirectory();
	std::string vertexShaderPath = rootPath;
	
	vertexShaderPath.append("\\Shaders\\DirectX11\\");
	vertexShaderPath.append(sFileName);
	std::wstring vertexShaderPathW(vertexShaderPath.begin(), vertexShaderPath.end());

	result = D3DX11CompileFromFile(vertexShaderPathW.c_str(), NULL, NULL, "DefaultVertexShader", VERTEX_SHADER_VERSION, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &pVertexShaderBuffer, &pErrorMessage, NULL);
	if(SUCCEEDED(result))
	{
		SAFE_RELEASE(pErrorMessage);

		// Compile the pixel shader code.
		result = D3DX11CompileFromFile(vertexShaderPathW.c_str(), NULL, NULL, "DefaultPixelShader", PIXEL_SHADER_VERSION, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
						   &pPixelShaderBuffer, &pErrorMessage, NULL);
		if(SUCCEEDED(result))
		{
			// Create the vertex shader from the buffer.
			if(SUCCEEDED(pGraphicsClass->GetDevice()->CreateVertexShader(pVertexShaderBuffer->GetBufferPointer(), pVertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader)))
			{
				// Now setup the layout of the data that goes into the shader.
				// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
				D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
				polygonLayout[0].SemanticName = "POSITION";
				polygonLayout[0].SemanticIndex = 0;
				polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				polygonLayout[0].InputSlot = 0;
				polygonLayout[0].AlignedByteOffset = 0;
				polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				polygonLayout[0].InstanceDataStepRate = 0;

				polygonLayout[1].SemanticName = "COLOR";
				polygonLayout[1].SemanticIndex = 0;
				polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				polygonLayout[1].InputSlot = 0;
				polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				polygonLayout[1].InstanceDataStepRate = 0;

				polygonLayout[2].SemanticName = "TEXCOORD";
				polygonLayout[2].SemanticIndex = 0;
				polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
				polygonLayout[2].InputSlot = 0;
				polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				polygonLayout[2].InstanceDataStepRate = 0;

				// Get a count of the elements in the layout.
				unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

				// Create the vertex input layout.
				result = pGraphicsClass->GetDevice()->CreateInputLayout(polygonLayout, numElements, pVertexShaderBuffer->GetBufferPointer(), 
									pVertexShaderBuffer->GetBufferSize(), &m_pLayout);
				if(SUCCEEDED(result))
				{
					bStatus = true;
				}
			}
			//END OF if(SUCCEEDED(pGraphicsClass->GetDevice()->CreateVertexShader(pVertexShaderBuffer->GetBufferPointer(), pVertexShaderBuffer->GetBufferSize(), NULL, &m_pVertexShader)))...

			if(SUCCEEDED(pGraphicsClass->GetDevice()->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(), pPixelShaderBuffer->GetBufferSize(), NULL, &m_pPixelShader)))
			{
				bStatus &= true;
			}
			else
			{
				bStatus = false;
			}

			// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
			D3D11_BUFFER_DESC matrixBufferDesc;
			matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
			matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			matrixBufferDesc.MiscFlags = 0;
			matrixBufferDesc.StructureByteStride = 0;

			// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
			if(SUCCEEDED(pGraphicsClass->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_pMatrixBuffer)))
			{
				// Create a texture sampler state description.
				D3D11_SAMPLER_DESC samplerDesc;
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.MipLODBias = 0.0f;
				samplerDesc.MaxAnisotropy = 1;
				samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				samplerDesc.BorderColor[0] = 0;
				samplerDesc.BorderColor[1] = 0;
				samplerDesc.BorderColor[2] = 0;
				samplerDesc.BorderColor[3] = 0;
				samplerDesc.MinLOD = 0;
				samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

				if(SUCCEEDED(pGraphicsClass->GetDevice()->CreateSamplerState(&samplerDesc, &m_pSampleState)))
				{
					bStatus &= true;
				}
				else
				{
					bStatus = false;
				}
			}
			else
			{
				bStatus = false;
			}
		}
		else
		{
			char* err = (char*)pErrorMessage->GetBufferPointer();
		}
	}
	else
	{
		char* err = (char*)(pErrorMessage->GetBufferPointer());
	}

	// Clean up regardless of the status.
	SAFE_RELEASE(pVertexShaderBuffer);
	SAFE_RELEASE(pPixelShaderBuffer);
	SAFE_RELEASE(pErrorMessage);

	return bStatus;
}

void D3DShaderClass::Render()
{
	if(m_pGraphicsClass == NULL)
		throw  NullArgumentException("D3DShaderClass", "Render", "m_pGraphicsClass");

	D3DGraphicsClass* pGraphicsClass = (D3DGraphicsClass*)m_pGraphicsClass;

	D3DCameraClass* pMasterCamera = (D3DCameraClass*)pGraphicsClass->GetMasterCamera();
	if(pMasterCamera == NULL)
		throw Exception("D3DShaderClass", "Render", "There is no master camera.  You need a camera to see!");

	D3DXMATRIX worldMatrix = pMasterCamera->GetWorldMatrix();
	D3DXMATRIX viewMatrix = pMasterCamera->GetViewMatrix();
	D3DXMATRIX projectionMatrix = pMasterCamera->GetProjectionMatrix();

	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	// Lock the constant buffer so it can be written to.
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = pGraphicsClass->GetDeviceContext()->Map(m_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		//return false;
		return;
	}

	// Get a pointer to the data in the constant buffer.
	MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	pGraphicsClass->GetDeviceContext()->Unmap(m_pMatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	unsigned int bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	pGraphicsClass->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_pMatrixBuffer);

	// Set the vertex input layout.
	pGraphicsClass->GetDeviceContext()->IASetInputLayout(m_pLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	pGraphicsClass->GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	pGraphicsClass->GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
	pGraphicsClass->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSampleState);

	return;
}

void D3DShaderClass::Shutdown()
{
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pMatrixBuffer);
	SAFE_RELEASE(m_pLayout);
	SAFE_RELEASE(m_pSampleState);
}