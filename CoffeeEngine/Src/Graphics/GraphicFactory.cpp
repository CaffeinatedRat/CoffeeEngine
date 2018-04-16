//--------------------------------------------------------------------------------------
// Description: The OpenGL model class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Graphics/IGraphics.hpp"
#include "System/ISystem.hpp"
#include "GraphicsUtility.hpp"
#include "BaseGraphicsClass.hpp"
#include <memory>

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using namespace CoffeeEngine::Interfaces;

#ifdef _WIN32
#include "DirectX/D3DGraphicsClass.hpp"
#include "OpenGL/WinOGLGraphicsClass.hpp"
using namespace CoffeeEngine::Graphics::DirectX;
using namespace CoffeeEngine::Graphics::OpenGL;
#else
#include "OpenGL/OGLGraphicsClass.hpp"
using namespace CoffeeEngine::Graphics::OpenGL;
#endif 

std::unique_ptr<BaseGraphicsClass> GraphicsFactory::CreateGraphics(GraphicsFactoryTypes graphicsType, ISystem *pSystem)
{
	switch (graphicsType)
	{
	#ifdef _WIN32
		case GraphicsFactoryTypes::DIRECTX:
			return std::make_unique<D3DGraphicsClass>(pSystem);

		case GraphicsFactoryTypes::OPENGL:
			return std::make_unique<WinOGLGraphicsClass>(pSystem);
			break;
	#else
		case GraphicsFactoryTypes::OPENGL:
			return std::make_unique<OGLGraphicsClass>(pSystem);
			break;
	#endif

	default:
		throw new NotSupportedException("GraphicsFactory", "CreateGraphics");
	}
}