//--------------------------------------------------------------------------------------
// Description: The Direct3d Graphics class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#include "stdafx.h"
#include "Common.hpp"
#include "D3DGraphicsClass.hpp"
#include "D3DModelClass.hpp"
#include "D3DShaderClass.hpp"
#include "D3DCameraClass.hpp"
#include "System/Win32/WindowsSystemClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::System;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Graphics::DirectX;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
D3DGraphicsClass::D3DGraphicsClass(const D3DGraphicsClass& object)
	: BaseGraphicsClass(object)
{
	m_pMasterCamera = object.m_pMasterCamera;
}

D3DGraphicsClass::~D3DGraphicsClass()
{
	Shutdown();
}

////////////////////////////////////////////////////////////
//
//                Public Methods
// 
////////////////////////////////////////////////////////////

bool D3DGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters)
{
	if(m_pSystem == nullptr)
		throw NullArgumentException("D3DGraphicsClass", "Initialize", "m_pSystem");
	
	m_pSystem->WriteToLog("[D3DGraphicsClass::Initialize] Begin", LogLevelType::Diagnostic);

	BaseGraphicsClass::Initialize(graphicsInitParameters);

	if(!CreateModeList())
	{
		Shutdown();
		return false;
	}

	if(!CreateSwapChain())
	{
		Shutdown();
		return false;
	}

	if(!CreateDepthBuffer())
	{
		Shutdown();
		return false;
	}

	if(!CreateRasterState())
	{
		Shutdown();
		return false;
	}

	SetViewport(0.0f, 0.0f, (float)m_graphicsPresentationProperties.screenWidth, (float)m_graphicsPresentationProperties.screenHeight);

	// Create an orthographic projection matrix for 2D rendering.
	m_orthoMatrix = XMMatrixOrthographicLH((float)graphicsInitParameters.screenWidth,
		(float)graphicsInitParameters.screenHeight,
		graphicsInitParameters.screenNear, 
		graphicsInitParameters.screenDepth);

	//We are ready to draw.
	m_displayReady = true;

	m_pSystem->WriteToLog("[D3DGraphicsClass::Initialize] End", LogLevelType::Diagnostic);
	return true;
}

void D3DGraphicsClass::BeginScene(float red, float green, float blue, float alpha)
{
	//Prevent scene drawing until initialization is complete.
	if(!m_displayReady)
		return;

	//Compile the clear colors (RGBA) into a single float array.
	float color[] = { red, green, blue, alpha };

	// Clear the back buffer.
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, color);

	// Clear the depth buffer.
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3DGraphicsClass::EndScene()
{
	//Prevent scene drawing until initialization is complete.
	if(!m_displayReady)
		return;

	// Present the back buffer to the screen since rendering is complete.
	m_pSwapChain->Present( ((m_graphicsPresentationProperties.vsyncEnabled) ? 1 : 0), 0);
}

void D3DGraphicsClass::Shutdown()
{
	m_pSystem->WriteToLog("[D3DGraphicsClass::Shutdown] Begin", LogLevelType::Diagnostic);

	m_displayReady = false;

	// Apparently, DirectX11 and possibly DirectX10 is not capable of closing while in fullscreen, so we have to reset the swap chain to windowed mode before we can release it.
	// According to www.DirectXTutorials.com, this is due to an implicit threading issue.
	if(m_pSwapChain)
	{
		m_pSwapChain->SetFullscreenState(false, nullptr);
	}

	//Release all of our modes.
	SAFE_ARRAY_DELETE(m_pDisplayModeList);

	//Safely release all of our dependencies.
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRasterState);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDepthStencilState);
	SAFE_RELEASE(m_pDepthStencilBuffer);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDeviceContext);

	m_videoCardDescription = "No Information Available.";
	m_numberOfModes = 0;

	m_pSystem->WriteToLog("[D3DGraphicsClass::Shutdown] End", LogLevelType::Diagnostic);
}

IModel* D3DGraphicsClass::CreateModel()
{
	return dynamic_cast<IModel*>(new D3DModelClass(this));
}

IShader* D3DGraphicsClass::CreateShader()
{
	return dynamic_cast<IShader*>(new D3DShaderClass(this));
}

ICamera* D3DGraphicsClass::CreateCamera()
{
	return dynamic_cast<ICamera*>(new D3DCameraClass(this));
}

void D3DGraphicsClass::SetMasterCamera(ICamera* camera)
{
	m_displayReady = false;
	m_pMasterCamera = (D3DCameraClass*)camera;
	m_displayReady = true;
}

//std::vector<std::string> D3DGraphicsClass::GetVideoCardInfo() const
//{
//	throw NotImplementedException("D3DGraphicsClass", "GetVideoCardInfo");
//}

/// <summary>
/// Sets the screen dimensions for the graphics presentation properties.
/// </summary>
void D3DGraphicsClass::SetScreenDimensions(int width, int height)
{
	if (height > 0)
	{
		m_graphicsPresentationProperties.screenWidth = width;
		m_graphicsPresentationProperties.screenHeight = height;

		if (m_pMasterCamera != nullptr)
			m_pMasterCamera->UpdateGraphicsProperties();

		ResetSwapChain();
		SetViewport(0.0f, 0.0f, (float)m_graphicsPresentationProperties.screenWidth, (float)m_graphicsPresentationProperties.screenHeight);
	}
}

////////////////////////////////////////////////////////////
//
//                Private Methods
// 
////////////////////////////////////////////////////////////

bool D3DGraphicsClass::CreateModeList()
{
	m_pSystem->WriteToLog("[D3DGraphicsClass::CreateModeList] Begin", LogLevelType::Diagnostic);

	//Locals.
	HRESULT result;
	bool status = false;
	IDXGIFactory* factory = nullptr;
	IDXGIAdapter* adapter = nullptr;
	DXGI_ADAPTER_DESC adapterDesc;
	IDXGIOutput* adapterOutput = nullptr;

	// Create a DirectX graphics interface factory.
	//NOTE: This is a more advanced method than created the IDirect3d9 interface, such as d3d = Direct3DCreate9(D3D_SDK_VERSION), by granting us access to the DirectX Graphics Interface.
	if(SUCCEEDED(result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		// Get the primary adapter.
		if(SUCCEEDED(result = factory->EnumAdapters(0, &adapter)))
		{
			// Get the adapter (video card) description.
			if(SUCCEEDED(result = adapter->GetDesc(&adapterDesc)))
			{
				// Store the dedicated video card memory in megabytes.
				m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

				// Convert the name of the video card to a character array and store it.
				size_t stringLength = 0;
				char tmp[128];
				if(wcstombs_s(&stringLength, tmp, 128, adapterDesc.Description, 128) == 0)
					m_videoCardDescription = tmp;

				// Get the primary output device, such as a monitor.
				if(SUCCEEDED(result = adapter->EnumOutputs(0, &adapterOutput)))
				{
					// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
					// Retrieve all of the supported modes for primary adapter and primary output device.
					// NOTE: We are looking for interlaced modes that support 8-bit ARGB channels that are unsigned and normalized (0,1) per channel.
					if(SUCCEEDED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &m_numberOfModes, NULL)))
					{
						// Allocate memory for our list of modes.
						if ((m_pDisplayModeList = new DXGI_MODE_DESC[m_numberOfModes]) != nullptr)
						{
							status = SUCCEEDED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &m_numberOfModes, m_pDisplayModeList));
						}
						//END OF if ((m_pDisplayModeList = new DXGI_MODE_DESC[m_numberOfModes]) == NULL )...
					}
					//END OF if(SUCCEEDED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &m_numberOfModes, NULL)))...
				}
				//END OF if(SUCCEEDED(result = adapter->EnumOutputs(0, &adapterOutput)))...
			}
			//END OF if(SUCCEEDED(result = adapter->GetDesc(&adapterDesc)))...
		}
		//END OF if(SUCCEEDED(result = factory->EnumAdapters(0, &adapter)))...
	}
	//END OF if(SUCCEEDED(result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))...

	// Clean up regardless of the status.
	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(adapter);
	SAFE_RELEASE(factory);

	m_pSystem->WriteToLog("[D3DGraphicsClass::CreateModeList] End", LogLevelType::Diagnostic);

	return status;
}

bool D3DGraphicsClass::CreateSwapChain()
{
	auto pSystem = dynamic_cast<WindowsSystemClass*>(m_pSystem);
	assert(pSystem);
	if (pSystem == nullptr)
		throw NullArgumentException("D3DGraphicsClass", "CreateSwapChain", "m_pSystem");

	pSystem->WriteToLog("[D3DGraphicsClass::CreateSwapChain] Begin", LogLevelType::Diagnostic);

	//Locals.
	HRESULT result;
	bool status = false;
	DXGI_RATIONAL refreshRate;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	//Initialize the refresh rate to zero.
	refreshRate.Denominator = 1;
	refreshRate.Numerator = 0;

	//If VSync is enabled, search for the matching refresh rate 
	if (m_graphicsPresentationProperties.vsyncEnabled)
	{
		pSystem->WriteToLog("[D3DGraphicsClass::CreateSwapChain] VSync is enabled, detecting refresh rate.");

		for (unsigned int i = 0; (i < m_numberOfModes && m_pDisplayModeList != nullptr); i++)
			if (m_pDisplayModeList[i].Width == (unsigned int)m_graphicsPresentationProperties.screenWidth)
				if (m_pDisplayModeList[i].Height == (unsigned int)m_graphicsPresentationProperties.screenHeight)
					refreshRate = m_pDisplayModeList[i].RefreshRate;
	}

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// We will only use one backbuffer at this time.
	swapChainDesc.BufferCount = 2;

	// Set the various backbuffer properties.
	swapChainDesc.BufferDesc.Width = m_graphicsPresentationProperties.screenWidth;
	swapChainDesc.BufferDesc.Height = m_graphicsPresentationProperties.screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate = refreshRate;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.Windowed = !(m_graphicsPresentationProperties.fullscreen);

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = pSystem->GetHWND();

	// Turn multisampling off for now...we'll have an option to enable this in the future.
	swapChainDesc.SampleDesc.Count = m_graphicsPresentationProperties.numberOfSamples;
	swapChainDesc.SampleDesc.Quality = 0;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	// Create the swap chain, Direct3D device, and Direct3D device context.
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, numFeatureLevels, 
		D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
	if (SUCCEEDED(result))
	{
		ID3D11Texture2D* backBufferPtr = nullptr;
		// Get the pointer to the back buffer.
		if (SUCCEEDED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr)))
		{
			auto featureLevel = m_pDevice->GetFeatureLevel();
			if (FEATURE_DESC_MAP.count(featureLevel))
			{
				std::stringstream featureMessage;
				featureMessage << "[D3DGraphicsClass::CreateSwapChain] Actual Version: " << FEATURE_DESC_MAP.at((uint)featureLevel);
				pSystem->WriteToLog(featureMessage);
			}

			// Create the render target view with the back buffer pointer.
			status = SUCCEEDED(m_pDevice->CreateRenderTargetView(backBufferPtr, NULL, &m_pRenderTargetView));
		}

		// Clean up regardless of the status.
		SAFE_RELEASE(backBufferPtr);

		pSystem->WriteToLog("[D3DGraphicsClass::CreateSwapChain] Completed successfully.");
	}
	else
	{
		if(result == E_INVALIDARG)
			throw Exception("D3DGraphicsClass", "CreateSwapChain", "DirectX is not supported on this machine.");
	}

	pSystem->WriteToLog("[D3DGraphicsClass::CreateSwapChain] End", LogLevelType::Diagnostic);
	return status;
}

bool D3DGraphicsClass::ResetSwapChain()
{
	m_pSystem->WriteToLog("[D3DGraphicsClass::ResetSwapChain] Begin", LogLevelType::Diagnostic);

	if (m_pDevice != nullptr && m_pDeviceContext != nullptr && m_pSwapChain != nullptr && m_pRenderTargetView != nullptr)
	{
		m_pDeviceContext->OMSetRenderTargets(0, 0, 0);

		// Release all outstanding references to the swap chain's buffers.
		m_pRenderTargetView->Release();

		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		if (SUCCEEDED(m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0)))
		{
			// Get the pointer to the back buffer.
			ID3D11Texture2D* pBuffer;
			bool status = false;
			if (SUCCEEDED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBuffer)))
			{
				// Create the render target view with the back buffer pointer.
				status = SUCCEEDED(m_pDevice->CreateRenderTargetView(pBuffer, NULL, &m_pRenderTargetView));
			}
			else
			{
				m_pSystem->WriteToLog("[D3DGraphicsClass::ResetSwapChain] Failed to GetBuffer.", LogLevelType::Error);
			}

			SAFE_RELEASE(pBuffer);

			if (status)
			{
				m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
				m_pSystem->WriteToLog("[D3DGraphicsClass::ResetSwapChain] End", LogLevelType::Diagnostic);
				return true;
			}
		}
		else
		{
			m_pSystem->WriteToLog("[D3DGraphicsClass::ResetSwapChain] Failed to ResizeBuffers.", LogLevelType::Error);
		}

		m_pSystem->WriteToLog("[D3DGraphicsClass::ResetSwapChain] Failed to reset the swap chain.", LogLevelType::Error);
		return false;
	}

	m_pSystem->WriteToLog("[D3DGraphicsClass::ResetSwapChain] End", LogLevelType::Diagnostic);
	return true;
}

bool D3DGraphicsClass::CreateDepthBuffer()
{
	m_pSystem->WriteToLog("[D3DGraphicsClass::CreateDepthBuffer] Begin", LogLevelType::Diagnostic);

	//Locals
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = m_graphicsPresentationProperties.screenWidth;
	depthBufferDesc.Height = m_graphicsPresentationProperties.screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	//Enable a 32-bit z-buffer with 24-bits for depth & 8-bits for stencil.
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//Disable multi-sampling (No AA)
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	//Determines if the CPU & GPU have access to this resource (currently the GPU has full access).
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	if(FAILED(m_pDevice->CreateTexture2D(&depthBufferDesc, NULL, &m_pDepthStencilBuffer)))
		return false;

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	if(FAILED(m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState)))
		return false;

	// Set the depth stencil state.
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	if(FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView)))
		return false;

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pSystem->WriteToLog("[D3DGraphicsClass::CreateDepthBuffer] End", LogLevelType::Diagnostic);
	return true;
}

bool D3DGraphicsClass::CreateRasterState()
{
	m_pSystem->WriteToLog("[D3DGraphicsClass::CreateRasterState] Begin", LogLevelType::Diagnostic);

	D3D11_RASTERIZER_DESC rasterDesc;

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = true;

	//rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = true;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	if(FAILED(m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState)))
		return false;

	// Now set the rasterizer state.
	m_pDeviceContext->RSSetState(m_pRasterState);

	m_pSystem->WriteToLog("[D3DGraphicsClass::CreateRasterState] End.", LogLevelType::Diagnostic);
	return true;
}

void D3DGraphicsClass::SetViewport(float x, float y, float width, float height)
{
	m_pSystem->WriteToLog("[D3DGraphicsClass::SetViewport] Begin", LogLevelType::Diagnostic);

	// Setup the viewport for rendering.
	D3D11_VIEWPORT viewport;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = x;
	viewport.TopLeftY = y;

	// Create the viewport.
	m_pDeviceContext->RSSetViewports(1, &viewport);

	m_pSystem->WriteToLog("[D3DGraphicsClass::SetViewport] End", LogLevelType::Diagnostic);
}

#endif