//--------------------------------------------------------------------------------------
// Description: The main engine.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _COFFEEENGINE_CLASS_H_
#define _COFFEEENGINE_CLASS_H_

#pragma once

#include <memory>

#include "Utility/Logger.hpp"
#include "Utility/LoggingTypes.hpp"
#include "System/ITimer.hpp"
#include "System/ISystem.hpp"
#include "System/ISystemListener.hpp"
#include "Graphics/GraphicsCommon.hpp"
#include "Graphics/BaseGraphicsClass.hpp"
#include "Graphics/ModelClass.hpp"

using namespace CoffeeEngine::Graphics;

namespace CoffeeEngine
{
	namespace Engine
	{
		enum class EngineState
		{
			SHUTDOWN = 0,
			INITIALIZED = 1,
			RUNNING = 2,
			RESTART_GRAPHICS = 3
		};

		class CoffeeEngineClass : public Interfaces::ISystemListener
		{
			//Restricting namespace scoping to within the class.
			using BaseGraphicsClass = CoffeeEngine::Graphics::BaseGraphicsClass;
			using Logger = CoffeeEngine::Utility::Logging::Logger;
			using LogLevelType = CoffeeEngine::Utility::Logging::LogLevelType;

		public:

			CoffeeEngineClass() = default;
			CoffeeEngineClass(Interfaces::ISystem*);
			CoffeeEngineClass(const CoffeeEngineClass&) = delete;
			virtual ~CoffeeEngineClass();

			////////////////////////////////////////////////////////////
			//
			//                Methods
			// 
			////////////////////////////////////////////////////////////

			/// <summary>
			/// This method initializes the engine.
			/// NOTE: This is invoked during the main function call by the OS entrypoint.
			/// </summary>
			bool Initialize();

			/// <summary>
			/// This method begins the engine.
			/// NOTE: This is invoked after a successful Initizlie and during the OS entrypoint.
			/// </summary>
			void Run();

			/// <summary>
			/// This method will shutdown the engine, clean up and release any resources.
			/// NOTE: This is automatically invoked after the class goes out of scope.
			/// </summary>
			void Shutdown();

		private:
			void Render(float elapsedTime);
			void ManageWorld(float elapsedTime);

			/// <summary>
			/// This method initializes the graphics display of the engine only.
			/// </summary>
			bool InitializeGraphics(GraphicsAPIType);

			/// <summary>
			/// This method will shutdown the graphics display of the engine only.
			/// </summary>
			void ShutdownGraphicsDisplay();

			////////////////////////////////////////////////////////////
			//
			//                Events
			// 
			////////////////////////////////////////////////////////////
		
		public:
			/// <summary>
			/// This event is usually triggered when the OS's message loop is idling and no events are occuring.
			/// </summary>
			virtual void OnIdle(bool) override;

			/// <summary>
			/// This event is usually triggered when a keydown event occurs.
			/// </summary>
			virtual void OnKeyDown(KeyboardKeys keyboardKey) override;

			/// <summary>
			/// This event is usually triggered when a keyup event occurs.
			/// </summary>
			virtual void OnKeyUp(KeyboardKeys keyboardKey) override;

			/// <summary>
			/// This event is usually triggered when keyup and keydown are not handled.
			/// </summary>
			virtual void OnChar(uint characterCode) override;

			/// <summary>
			/// This event is usually triggered when the graphis type has changed
			/// </summary>
			virtual bool OnGraphicsReset(GraphicsAPIType graphicsAPIType) override;

			/// <summary>
			/// This event is usually triggered when a window is resized.
			/// </summary>
			virtual void OnWindowResize(int width, int height) override;

			////////////////////////////////////////////////////////////
			//
			//                Member Vars
			// 
			////////////////////////////////////////////////////////////
		private:
			//Reference pointers.
			Interfaces::ISystem* m_pSystem = nullptr;
			Interfaces::ITimer* m_pTimer = nullptr;
			Logger *m_pLogger = nullptr;

			//Graphics states.
			std::unique_ptr<BaseGraphicsClass> m_upGraphics = nullptr;
			GraphicsAPIType m_graphicsType;

			//Temporary for testing.
			Interfaces::ICamera* m_pCamera = nullptr;
			Interfaces::IModel* m_pModel = nullptr;
			Interfaces::IShader* m_pShader = nullptr;

			//Engine states.
			bool m_bReady = false;
			EngineState m_state = EngineState::SHUTDOWN;

			float m_strafeMovement = 0.0f;
			float m_pitchMovement = 0.0f;
			float m_turnMovement = 0.0f;
			float m_forwardMovement = 0.0f;
		};
	};
};

#endif
