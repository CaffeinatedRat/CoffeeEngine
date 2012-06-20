//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _COFFEEENGINE_CLASS_H_
#define _COFFEEENGINE_CLASS_H_

#include "stdafx.h"
#include "Common.h"

#include "Interfaces\ISystem.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Graphics\ModelClass.h"

using namespace CoffeeEngine::Interfaces;
using namespace CoffeeEngine::Graphics;

namespace CoffeeEngine
{
	namespace Engine
	{
		class CoffeeEngineClass
		{
		public:
		
			CoffeeEngineClass();
			CoffeeEngineClass(ISystem* pSystem, BaseGraphicsClass* pGraphics);
			~CoffeeEngineClass();

			bool Initialize();
			void Run();
			void Render();
			bool Frame();
			void Shutdown();
		
		private:
			BaseGraphicsClass* m_pGraphics;

			ISystem* m_pSystem;
			ICamera* m_pCamera;

			//Temporary for testing.
			IModel* m_pModel;
			IShader* m_pShader;
		};
	};
};

#endif