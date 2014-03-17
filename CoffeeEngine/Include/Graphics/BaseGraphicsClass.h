//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _BASE_GRAPHICS_CLASS_H_
#define _BASE_GRAPHICS_CLASS_H_

#include "Interfaces/ISystem.h"
#include "Interfaces/IGraphics.h"
#include "Interfaces/IModel.h"
#include "Common.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class BaseGraphicsClass : public IGraphics
		{
		protected:
			ISystem* m_pSystem;
			std::string m_sGraphicsLibraryName;

		protected:

			BaseGraphicsClass();

		public:

			BaseGraphicsClass(ISystem* pSystem, std::string sGraphicsLibraryName);
			BaseGraphicsClass(const BaseGraphicsClass& object);
			virtual ~BaseGraphicsClass() { };

			/// <summary>
			/// Returns the current operating system interface.
			/// </summary>
			/// <returns>
			/// Returns the current operating system.
			/// </returns>
			inline ISystem* GetSystem() { return m_pSystem; }

			/// <summary>
			/// Returns the current graphics library.
			/// </summary>
			std::string GetGraphicsLibraryName() { return m_sGraphicsLibraryName; }
		};
	};
};

#endif