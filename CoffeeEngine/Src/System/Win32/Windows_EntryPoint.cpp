//--------------------------------------------------------------------------------------
// Description: Defines the WINDOWS entry point for the application.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "System/Win32/Windows_EntryPoint.h"
#include "System/Win32/WindowsSystemClass.h"
#include "Global.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::System;

int WinMain_ENTRY(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//NOTE: This is used to suppress the W4 warning.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//Instantiate the main windows operating system object.
	if( (g_pSystem = new WindowsSystemClass()) != NULL)
	{
		//Attempt to initialize the operating system object and run it if initialization is successful.
		if(g_pSystem->Initialize())
			g_pSystem->Run();

		//Shutdown and release the memory.
		g_pSystem->Shutdown();
		delete g_pSystem;
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
	if(g_pSystem)
		return ((WindowsSystemClass*)g_pSystem)->MessageHandler(hWnd, message, wParam, lParam);
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}