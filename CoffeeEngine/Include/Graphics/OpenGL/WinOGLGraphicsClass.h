//--------------------------------------------------------------------------------------
// Description: The Windows version of OpenGL
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _WIN_OPENGL_CLASS_H_
#define _WIN_OPENGL_CLASS_H_

#include "stdafx.h"
#include "Graphics\OpenGL\OGLGraphicsClass.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class WinOGLGraphicsClass : public OGLGraphicsClass
			{
			private:

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////
				HGLRC m_renderingContext;
				HDC m_hdc;

			public:
		
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				WinOGLGraphicsClass(ISystem* pSystem);
				WinOGLGraphicsClass(const WinOGLGraphicsClass& object);
				virtual ~WinOGLGraphicsClass();

				/// <summary>
				/// Attempts to initialize the graphics object.
				/// </summary>
				/// <returns>
				/// Returns true if initialization was successful.
				/// </returns>
				virtual bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters);

				/// <summary>
				/// Begins the rendering process.
				/// </summary>
				virtual void BeginScene(float, float, float, float);

				/// <summary>
				/// Ends the rendering process.
				/// </summary>
				virtual void EndScene();

				/// <summary>
				/// Begins the process of shutting down the graphics class and all dependencies.
				/// </summary>
				virtual void Shutdown();
			};
		};
	};
};

#endif