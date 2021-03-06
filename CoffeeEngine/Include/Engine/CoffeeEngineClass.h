//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _COFFEEENGINE_CLASS_H_
#define _COFFEEENGINE_CLASS_H_

#pragma once

//#include "stdafx.h"
//#include "Common.h"

#include <memory>

#include "Utility/Logger.h"
#include "Utility/LoggingTypes.h"
#include "Interfaces/ITimer.h"
#include "Interfaces/ISystem.h"
#include "Interfaces/ISystemListener.h"
#include "Graphics/BaseGraphicsClass.h"
#include "Graphics/ModelClass.h"

namespace CoffeeEngine
{
	namespace Engine
	{
		//Restricting namespace scoping to within the class.
		using BaseGraphicsClass = CoffeeEngine::Graphics::BaseGraphicsClass;
		using Logger = CoffeeEngine::Utility::Logging::Logger;
		using LogLevelType = CoffeeEngine::Utility::Logging::LogLevelType;

		class CoffeeEngineClass : public Interfaces::ISystemListener
		{
		public:

			CoffeeEngineClass() = default;
			CoffeeEngineClass(Interfaces::ISystem*);
			virtual ~CoffeeEngineClass();

			bool Initialize();
			void Run();
			void Render();

			/// <summary>
			/// This event is usually triggered when the OS's message loop is idling and no events are occuring.
			/// </summary>
			virtual void OnIdle(bool) override;

			/// <summary>
			/// This method will shutdown the engine, clean up and release any resources.
			/// </summary>
			void Shutdown();

		private:
			//Reference pointers.
			Interfaces::ISystem* m_pSystem = nullptr;
			Logger *m_pLogger = nullptr;

			std::unique_ptr<BaseGraphicsClass> m_upGraphics = nullptr;

			Interfaces::ICamera* m_pCamera = nullptr;
			Interfaces::ITimer* m_pTimer = nullptr;

			//Temporary for testing.
			Interfaces::IModel* m_pModel = nullptr;
			Interfaces::IShader* m_pShader = nullptr;

			bool m_bReady = false;
		};
	};
};

#endif