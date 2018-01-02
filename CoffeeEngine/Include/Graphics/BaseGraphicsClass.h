//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _BASE_GRAPHICS_CLASS_H_
#define _BASE_GRAPHICS_CLASS_H_

#include "Common.h"
#include "Interfaces/ISystem.h"
#include "Interfaces/IGraphics.h"

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
		};
	};
};

#endif