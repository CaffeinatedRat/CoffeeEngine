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

			BaseGraphicsClass() = delete;
			BaseGraphicsClass(ISystem* pSystem, std::string sGraphicsLibraryName);
			BaseGraphicsClass(const BaseGraphicsClass& object) noexcept;
			BaseGraphicsClass(BaseGraphicsClass&& object) noexcept;
			virtual ~BaseGraphicsClass() { };

			BaseGraphicsClass& operator=(BaseGraphicsClass&&) = default;
			BaseGraphicsClass& operator=(const BaseGraphicsClass&) = default;

			/// <summary>
			/// Attempts to initialize the graphics object.
			/// </summary>
			/// <returns>
			/// Returns true if initialization was successful.
			/// </returns>
			virtual bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters) override;

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
			std::string GetGraphicsLibraryName() const { return m_sGraphicsLibraryName; }

		protected:
			ISystem *m_pSystem = nullptr;
			std::string m_sGraphicsLibraryName = "Undefined";

			//Primitives
			bool m_bFullScreen = false;
			bool m_bDisplayReady = false;
			bool m_bVsyncEnabled = false;
			int m_nScreenWidth = 0;
			int m_nScreenHeight = 0;
			int m_videoCardMemory = 0;
			uint m_nNumOfModes = 0;
			float m_ScreenDepth = 0.0f;
			float m_ScreenNear = 0.0f;

			GRAPHICS_VERSION m_version;
		};
	};
};

#endif
