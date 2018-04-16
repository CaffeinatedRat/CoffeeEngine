//--------------------------------------------------------------------------------------
// Description: The graphics interface.  Used to provide a light-weight skeleton of how the other graphics classes should be created.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _IGRAPHICS_INTERFACE_H_
#define _IGRAPHICS_INTERFACE_H_

#pragma once

#include "Common.hpp"
#include "IModel.hpp"
#include "ICamera.hpp"
#include "IShader.hpp"
#include "System/ISystem.hpp"
#include "Graphics/GraphicsCommon.hpp"

namespace CoffeeEngine
{
	namespace Interfaces
	{
		class IGraphics
		{
		public:
		
			/// <summary>
			/// Attempts to initialize the graphics object.
			/// </summary>
			/// <returns>
			/// Returns true if initialization was successful.
			/// </returns>
			virtual bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS&) = 0;

			/// <summary>
			/// Begins the rendering process.
			/// </summary>
			virtual void BeginScene(float, float, float, float) = 0;
			
			/// <summary>
			/// Ends the rendering process.
			/// </summary>			
			virtual void EndScene() = 0;

			/// <summary>
			/// Begins the process of shutting down the graphics class and all dependencies.
			/// </summary>
			virtual void Shutdown() = 0;

			/// <summary>
			/// Returns the current operating system interface.
			/// </summary>
			/// <returns>
			/// Returns the current operating system.
			/// </returns>
			virtual const ISystem* GetSystem() const noexcept = 0;


			/// <summary>
			/// Creates a new model for the specific graphics engine.
			/// NOTE: This creates a new instance of the object.  It is your responsibility to delete this instance when done with it.
			/// </summary>
			/// <returns>
			/// Returns a newly created model.
			/// </returns>
			virtual IModel* CreateModel() = 0;

			/// <summary>
			/// Creates a new shader for the specific graphics engine.
			/// NOTE: This creates a new instance of the object.  It is your responsibility to delete this instance when done with it.
			/// </summary>
			/// <returns>
			/// Returns a newly created shader.
			/// </returns>
			virtual IShader* CreateShader() = 0;

			/// <summary>
			/// Creates a new camera for the specific graphics engine.
			/// NOTE: This creates a new instance of the object.  It is your responsibility to delete this instance when done with it.
			/// </summary>
			/// <returns>
			/// Returns a newly created camnera.
			/// </returns>
			virtual ICamera* CreateCamera() = 0;

			/// <summary>
			/// Sets the master camera.
			/// </summary>
			virtual void SetMasterCamera(ICamera* camera) = 0;

			/// <summary>
			/// Gets the master camera.
			/// </summary>
			/// <returns>
			/// Returns an instance of the master camera.
			/// </returns>
			virtual ICamera* GetMasterCamera() const = 0;

			/// <summary>
			/// Returns a block of information about the video card.
			/// </summary>
			/// <returns>
			/// Returns a compliant list of video card information.
			/// </returns>
			virtual std::vector<std::string> GetVideoCardInfo() const = 0;

			/// <summary>
			/// Returns the current graphics library.
			/// </summary>
			virtual std::string GetGraphicsLibraryName() const = 0;
		};
	};
};

#endif
