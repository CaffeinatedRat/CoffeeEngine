//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _BASE_GRAPHICS_CLASS_H_
#define _BASE_GRAPHICS_CLASS_H_

#include "Common.hpp"
#include "Interfaces/ISystem.hpp"
#include "Interfaces/IGraphics.hpp"

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
			virtual ~BaseGraphicsClass() { };

			/// <summary>
			/// Returns the current operating system interface.
			/// </summary>
			/// <returns>
			/// Returns the current operating system.
			/// </returns>
			inline const ISystem* GetSystem() const noexcept { return m_pSystem; }

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
			unsigned int m_nNumOfModes = 0;
			GRAPHICS_VERSION m_version;
		};
	};
};

#endif
