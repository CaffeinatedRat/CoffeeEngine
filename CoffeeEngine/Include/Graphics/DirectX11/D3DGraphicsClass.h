//--------------------------------------------------------------------------------------
// Description: The Direct3d Graphics class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _D3DGRAPHICS_CLASS_H_
#define _D3DGRAPHICS_CLASS_H_

#include "Common.h"
#include "Interfaces\ISystem.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\GraphicsCommon.h"

#include "Graphics\DirectX11\D3DCommon.h"
#include "Graphics\DirectX11\D3DCameraClass.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX11
		{
			class D3DGraphicsClass : public BaseGraphicsClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				//Primitives
				bool m_bFullScreen;
				bool m_bDisplayReady;
				bool m_bVsyncEnabled;
				int m_nScreenWidth;
				int m_nScreenHeight;
				int m_videoCardMemory;
				std::string m_videoCardDescription;
				unsigned int m_nNumOfModes;

				//Direct3d
				DXGI_MODE_DESC* m_pDisplayModeList;
				IDXGISwapChain* m_pSwapChain;
				ID3D11Device* m_pDevice;
				ID3D11DeviceContext* m_pDeviceContext;
				ID3D11RenderTargetView* m_pRenderTargetView;
				ID3D11Texture2D* m_pDepthStencilBuffer;
				ID3D11DepthStencilState* m_pDepthStencilState;
				ID3D11DepthStencilView* m_pDepthStencilView;
				ID3D11RasterizerState* m_pRasterState;

				D3DXMATRIX m_orthoMatrix;

				//CoffeeEngine constructs.
				D3DCameraClass* m_pMasterCamera;

			public:
		
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				D3DGraphicsClass(ISystem* pSystem);
				D3DGraphicsClass(const D3DGraphicsClass& object);
				virtual ~D3DGraphicsClass();

				/// <summary>
				/// Attempts to initialize the graphics object.
				/// </summary>
				/// <returns>
				/// Returns true if initialization was successful.
				/// </returns>
				bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters);

				/// <summary>
				/// Begins the rendering process.
				/// </summary>
				void BeginScene(float, float, float, float);

				/// <summary>
				/// Ends the rendering process.
				/// </summary>
				void EndScene();

				/// <summary>
				/// Begins the process of shutting down the graphics class and all dependencies.
				/// </summary>
				void Shutdown();

				/// <summary>
				/// Creates a new model for the specific graphics engine.
				/// </summary>
				/// <returns>
				/// Returns a newly created model.
				/// </returns>
				IModel* CreateModel();

				/// <summary>
				/// Creates a new shader for the specific graphics engine.
				/// </summary>
				/// <returns>
				/// Returns a newly created shader.
				/// </returns>
				IShader* CreateShader();

				/// <summary>
				/// Creates a new camera for the specific graphics engine.
				/// </summary>
				/// <returns>
				/// Returns a newly created camnera.
				/// </returns>
				ICamera* CreateCamera();

				/// <summary>
				/// Sets the master camera.
				/// </summary>
				void SetMasterCamera(ICamera* camera);

				/// <summary>
				/// Gets the master camera.
				/// </summary>
				/// <returns>
				/// Returns an instance of the master camera.
				/// </returns>
				inline ICamera* GetMasterCamera() { return m_pMasterCamera; }

				/// <summary>
				/// Returns a block of information about the video card.
				/// </summary>
				/// <returns>
				/// Returns a compliant list of video card information.
				/// </returns>
				std::vector<std::string> GetVideoCardInfo();

				////////////////////////////////////////////////////////////
				//
				//                Transition methods
				// 
				////////////////////////////////////////////////////////////

				inline void GetScreenProperties(int& nWidth, int& nHeight)
				{
					nWidth = m_nScreenWidth;
					nHeight = m_nScreenHeight;
				}

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////
			public:
				inline ID3D11Device* GetDevice() { return m_pDevice; }
				inline ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext; }

				inline D3DXMATRIX& GetOrthoMatrix() { return m_orthoMatrix; }

			private:
				
				/// <summary>
				/// Creates a list of modes based on the available adapter and outputs.
				/// </summary>
				/// <returns>
				/// True if the mode list was constructed.
				/// </returns>
				bool CreateModeList();

				/// <summary>
				/// Creates the swap chain and render target view.
				/// </summary>
				/// <returns>
				/// True if the swap chain and render target view have been created.
				/// </returns>
				bool CreateSwapChain();
				
				/// <summary>
				/// Creates a depth buffer, stencil, and view.
				/// </summary>
				/// <returns>
				/// True if the depth buffer was successfully created.
				/// </returns>
				bool CreateDepthBuffer();

				/// <summary>
				/// Creates a raster state.
				/// </summary>
				/// <returns>
				/// True if the raster state was successfully created.
				/// </returns>
				bool CreateRasterState();

				/// <summary>
				/// Create a viewport.
				/// </summary>
				/// <returns>
				/// True if the viewport was successfully created.
				/// </returns>
				bool CreateViewPort();
			};
		};
	};
};

#endif