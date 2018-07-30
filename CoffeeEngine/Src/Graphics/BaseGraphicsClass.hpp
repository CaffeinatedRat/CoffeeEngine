//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _BASE_GRAPHICS_CLASS_H_
#define _BASE_GRAPHICS_CLASS_H_

#include "Common.hpp"
#include "System/ISystem.hpp"
#include "IGraphics.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class BaseGraphicsClass : public IGraphics
		{
		public:

			////////////////////////////////////////////////////////////
			//
			//            Constructors/Assignment Operators
			// 
			////////////////////////////////////////////////////////////

			BaseGraphicsClass() = delete;
			BaseGraphicsClass(ISystem* pSystem, std::string sGraphicsLibraryName);
			BaseGraphicsClass(const BaseGraphicsClass& object) noexcept;
			BaseGraphicsClass(BaseGraphicsClass&& object) noexcept;
			virtual ~BaseGraphicsClass() { };

			BaseGraphicsClass& operator=(BaseGraphicsClass&&) = default;
			BaseGraphicsClass& operator=(const BaseGraphicsClass&) = default;

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
			virtual bool Initialize(const GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters) override;

			/// <summary>
			/// Returns the current operating system interface.
			/// </summary>
			/// <returns>
			/// Returns the current operating system.
			/// </returns>
			inline ISystem* GetSystem() const noexcept { return m_pSystem; }

			/// <summary>
			/// Returns the current graphics library.
			/// </summary>
			inline std::string GetGraphicsLibraryName() const noexcept  { return m_graphicsLibraryName; }

			////////////////////////////////////////////////////////////
			//
			//                Graphics Properties Methods
			// 
			////////////////////////////////////////////////////////////

			/// <summary>
			/// Returns a constant refernece to the graphics presentation properties.
			/// </summary>
			inline const GRAPHICS_PRESENTATION_PROPERTIES& GetGraphicsPresentationProperties() const { return m_graphicsPresentationProperties; }

			/// <summary>
			/// Sets the screen dimensions for the graphics presentation properties.
			/// </summary>
			inline virtual void SetScreenDimensions(int width, int height)
			{
				m_graphicsPresentationProperties.screenWidth = width;
				m_graphicsPresentationProperties.screenHeight = height;
			}

		protected:
			ISystem *m_pSystem = nullptr;
			std::string m_graphicsLibraryName = "Undefined";

			//Primitives
			bool m_displayReady = false;
			int m_videoCardMemory = 0;
			uint m_numberOfModes = 0;

			//
			int m_width = 0, m_height = 0;

			//Store the initial graphics parameters.  These should be constant once set.
			GRAPHICS_PRESENTATION_PROPERTIES m_graphicsPresentationProperties;
		};
	};
};

#endif
