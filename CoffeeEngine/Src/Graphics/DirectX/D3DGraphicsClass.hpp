//--------------------------------------------------------------------------------------
// Description: The Direct3d Graphics class.
// Reference: Thanks to RasterTek (www.rastertek.com) for the DirectX11 samples that served as the foundation and framework for some of these D3DClasses.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#pragma once
#ifndef _D3DGRAPHICS_CLASS_H_
#define _D3DGRAPHICS_CLASS_H_

#include "Common.hpp"
#include "System/ISystem.hpp"
#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/GraphicsCommon.hpp"

#include "Graphics/DirectX/D3DCommon.hpp"
#include "Graphics/DirectX/D3DCameraClass.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace DirectX
		{
			class D3DGraphicsClass : public BaseGraphicsClass
			{
			public:
		
				////////////////////////////////////////////////////////////
				//
				//            Constructors/Assignment Operators
				// 
				////////////////////////////////////////////////////////////

				D3DGraphicsClass() = delete;
				D3DGraphicsClass(ISystem* pSystem) : BaseGraphicsClass(pSystem, "DirectX") {};
				D3DGraphicsClass(const D3DGraphicsClass& object);
				virtual ~D3DGraphicsClass();

				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				/// <summary>
				/// Attempts to initialize the graphics object.
				/// </summary>
				/// <returns>
				/// Returns true if initialization was successful.
				/// </returns>
				bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters) override;

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
				inline ICamera* GetMasterCamera() const { return m_pMasterCamera; }

				/// <summary>
				/// Returns a block of information about the video card.
				/// </summary>
				/// <returns>
				/// Returns a compliant list of video card information.
				/// </returns>
				//std::vector<std::string> GetVideoCardInfo() const;

				////////////////////////////////////////////////////////////
				//
				//                Graphics Properties Methods
				// 
				////////////////////////////////////////////////////////////

				/// <summary>
				/// Sets the screen dimensions for the graphics presentation properties.
				/// </summary>
				virtual void SetScreenDimensions(int width, int height) override;

				////////////////////////////////////////////////////////////
				//
				//                DirectX Specific methods
				// 
				////////////////////////////////////////////////////////////
				inline ID3D11Device* GetDevice() const { return m_pDevice; }
				inline ID3D11DeviceContext* GetDeviceContext() const { return m_pDeviceContext; }

				inline XMMATRIX& GetOrthoMatrix() { return m_orthoMatrix; }

			private:
				
				/// <summary>
				/// Creates a list of modes based on the available adapter and outputs.
				/// </summary>
				bool CreateModeList();

				/// <summary>
				/// Creates the swap chain and render target view.
				/// </summary>
				bool CreateSwapChain();
				
				/// <summary>
				/// Resets the swap chain.
				/// </summary>
				bool ResetSwapChain();

				/// <summary>
				/// Creates a depth buffer, stencil, and view.
				/// </summary>
				bool CreateDepthBuffer();

				/// <summary>
				/// Creates a raster state.
				/// </summary>
				bool CreateRasterState();

				/// <summary>
				/// Sets the viewport.
				/// </summary>
				void SetViewport(float x, float y, float width, float height);

			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				//Primitives
				std::string m_videoCardDescription = "No Information Available.";

				//Direct3d
				DXGI_MODE_DESC* m_pDisplayModeList = nullptr;
				IDXGISwapChain* m_pSwapChain = nullptr;
				ID3D11Device* m_pDevice = nullptr;
				ID3D11DeviceContext* m_pDeviceContext = nullptr;
				ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
				ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
				ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
				ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
				ID3D11RasterizerState* m_pRasterState = nullptr;

				XMMATRIX m_orthoMatrix;

				//By default there is no master camera.
				D3DCameraClass* m_pMasterCamera = nullptr;
			};
		};
	};
};

#endif

#endif
