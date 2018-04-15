//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _GRAPHICS_UTILITY_H_
#define _GRAPHICS_UTILITY_H_

#pragma once

#include "Common.hpp"
#include "Interfaces/ISystem.hpp"
#include "Graphics/GraphicsCommon.hpp"
#include "Graphics/BaseGraphicsClass.hpp"

#include <memory>

namespace CoffeeEngine
{
	namespace Graphics
	{
		struct GraphicsFactory
		{
			using ISystem = CoffeeEngine::Interfaces::ISystem;
			using BaseGraphicsClass = Graphics::BaseGraphicsClass;
			static std::unique_ptr<BaseGraphicsClass> CreateGraphics(GraphicsFactoryTypes graphicsType, ISystem *pSystem);
		};
	};
};

#endif
