//--------------------------------------------------------------------------------------
// Description: Defines the main entry point for the application.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#ifdef _WIN32

	////////////////////////////////////////////////////////////////////////////////
	// Header file's required:
	// 1) Windows_EntryPoint.h -- Entry point into windows based systems.
	/////////////////////////////////////////////////////////////////////////////////

	#include "System/Win32/Windows_EntryPoint.hpp"

	int APIENTRY _tWinMain(HINSTANCE hInstance,
						 HINSTANCE hPrevInstance,
						 LPTSTR    lpCmdLine,
						 int       nCmdShow)
	{
		return WinMain_ENTRY(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}

#elif __linux__

	////////////////////////////////////////////////////////////////////////////////
	// Header file's required:
	// 1) linux_entrypoint.h -- Entry point into linux & linux based systems.
	/////////////////////////////////////////////////////////////////////////////////
	#include "System/Linux/Linux_EntryPoint.hpp"

	int main(int argc, char *argv[])
	{
		return linux_main(argc, argv);
	}

#endif