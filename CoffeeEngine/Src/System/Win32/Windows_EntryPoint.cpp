//--------------------------------------------------------------------------------------
// Description: Defines the WINDOWS entry point for the application.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#include <memory>
#include "Common.hpp"
#include "Windows_EntryPoint.hpp"
#include "WindowsSystemClass.hpp"
#include "Engine/CoffeeEngineClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Utility::Logging;
using namespace CoffeeEngine::Engine;
using namespace CoffeeEngine::System;

static std::unique_ptr<Logger> pLogger;
static std::unique_ptr<ISystem> pSystem;

int WinMain_ENTRY(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	//NOTE: This is used to suppress the W4 warning.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	try
	{
		//Attempt to create the logger and set the verbosity.
		//Bail if we are unable to create the logger.
		pLogger = std::make_unique<Logger>(Logger::LOG_FILE_NAME, Verbosity::Normal);
		assert(pLogger);
		if (!pLogger)
			return -1;
	}
	catch (...) {}

	std::unique_ptr<CoffeeEngineClass> pCoffeeEngine;

	try
	{
		//Instantiate the main windows operating system object. 
		pSystem = std::make_unique<WindowsSystemClass>(pLogger.get());
		assert(pSystem);
		
		//Attempt to instantiate the CoffeeEngine, it will now handle initializing the OS component.
		pCoffeeEngine = std::make_unique<CoffeeEngineClass>(pSystem.get());
		
		//Initialize the engine and begin running.
		if (pCoffeeEngine->Initialize())
			pCoffeeEngine->Run();
	}
	catch (Exception& exception)
	{
		//Known exceptions we've thrown.
		if (pLogger)
			pLogger->Write(exception);
	}
	catch (std::bad_alloc& badAllocException)
	{
		//Memory allocation failures.
		if (pLogger)
		{
			auto sMemoryAllocationError = std::string("[WinMain_ENTRY] Memory allocation error --> ");
			sMemoryAllocationError.append(badAllocException.what());
			pLogger->Write(sMemoryAllocationError, LogLevelType::Error);
		}
	}
	catch (...)
	{
		//Unhandled exception.
		if (pLogger)
			pLogger->Write("[WinMain_ENTRY] Unknown exception!", LogLevelType::Error);
	}

	return 0;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pSystem && pSystem.get() != nullptr)
		return static_cast<WindowsSystemClass*>(pSystem.get())->MessageHandler(hWnd, message, wParam, lParam);
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}

#endif