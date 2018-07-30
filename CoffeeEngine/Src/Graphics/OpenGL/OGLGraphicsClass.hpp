//--------------------------------------------------------------------------------------
// Description: The OpenGL Graphics class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _OGLGRAPHICS_CLASS_H_
#define _OGLGRAPHICS_CLASS_H_

#pragma once

#include "Common.hpp"
#include "System/ISystem.hpp"
#include "Graphics/GraphicsCommon.hpp"
#include "Graphics/BaseGraphicsClass.hpp"

#include "OGLCommon.hpp"
#include "OGLCameraClass.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class OGLGraphicsClass : public BaseGraphicsClass
			{
			public:
		
				////////////////////////////////////////////////////////////
				//
				//            Constructors/Assignment Operators
				// 
				////////////////////////////////////////////////////////////

				OGLGraphicsClass() = delete;
				OGLGraphicsClass(ISystem* pSystem) : BaseGraphicsClass(pSystem, "OpenGL") {};
				OGLGraphicsClass(const OGLGraphicsClass& object);
				virtual ~OGLGraphicsClass() = 0;

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
				virtual bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters) override = 0;

				/// <summary>
				/// Begins the rendering process.
				/// </summary>
				void BeginScene(float, float, float, float) = 0;

				/// <summary>
				/// Ends the rendering process.
				/// </summary>
				void EndScene();

				/// <summary>
				/// Begins the process of shutting down the graphics class and all dependencies.
				/// </summary>
				virtual void Shutdown();

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
				inline ICamera* GetMasterCamera() const override { return m_pMasterCamera; }

				/// <summary>
				/// Returns a block of information about the video card.
				/// </summary>
				/// <returns>
				/// Returns a compliant list of video card information.
				/// </returns>
				//std::vector<std::string> GetVideoCardInfo() const override;

				////////////////////////////////////////////////////////////
				//
				//                Graphics Properties Methods
				// 
				////////////////////////////////////////////////////////////

				/// <summary>
				/// Sets the screen dimensions for the graphics presentation properties.
				/// </summary>
				virtual void SetScreenDimensions(int width, int height) override;

			protected:
				/// <summary>
				/// Safely initializes the Glew context once.
				/// This method is idempotent.
				/// </summary>
				virtual bool InitializeGlew();

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
				/// Sets the viewport.
				/// </summary>
				void SetViewport(int x, int y, int width, int height);

			protected:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////

				bool m_isGlewInitialized = false;
				std::string m_videoCardDescription = "No Information Available.";
				std::string m_actualVersionInfo = "No version info available.";

				//By default there is no master camera.
				OGLCameraClass *m_pMasterCamera = nullptr;
			};
		};
	};
};

#endif
