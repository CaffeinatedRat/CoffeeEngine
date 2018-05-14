//--------------------------------------------------------------------------------------
// Description: The Windows version of OpenGL
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#ifndef _WIN_OPENGL_CLASS_H_
#define _WIN_OPENGL_CLASS_H_

#pragma once

#include "stdafx.h"
#include "OGLGraphicsClass.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class WinOGLGraphicsClass : public OGLGraphicsClass
			{
			public:
		
				////////////////////////////////////////////////////////////
				//
				//                Standard methods
				// 
				////////////////////////////////////////////////////////////

				WinOGLGraphicsClass() = delete;
				WinOGLGraphicsClass(ISystem* pSystem) : OGLGraphicsClass(pSystem) {}
				WinOGLGraphicsClass(const WinOGLGraphicsClass& object);
				virtual ~WinOGLGraphicsClass();

				/// <summary>
				/// Attempts to initialize the graphics object.
				/// </summary>
				/// <returns>
				/// Returns true if initialization was successful.
				/// </returns>
				virtual bool Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters) override;

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
				virtual void Shutdown() override;

				/// <summary>
				/// Windows Message Handler for Glew
				/// </summary>
				//LRESULT CALLBACK MessageHandlerGlew(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			protected:
				/// <summary>
				/// Safely initializes the Glew context once.
				/// </summary>
				virtual bool InitializeGlew() override;

			private:
				/// <summary>
				/// Registers the Glew specific windows class.
				/// </summary>
				void RegisterGlewClass(HINSTANCE hInstance);

				const TCHAR* GLEW_CLASS_NAME = _T("GLEW_WINDOW");
				const TCHAR* GLEW_WINDOW_TITLE = _T("GLEW WINDOW");

				////////////////////////////////////////////////////////////
				//
				//                Member Vars
				// 
				////////////////////////////////////////////////////////////
				HGLRC m_renderingContext = nullptr;
				HDC m_hdc = nullptr;
				bool m_bGlewClassRegistered = false;
			};
		};
	};
};



#endif

#endif
