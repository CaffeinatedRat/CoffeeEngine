//--------------------------------------------------------------------------------------
// Description: Defines the LINUX entry point for the application.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#ifdef __linux__

#include "System/Linux/Linux_EntryPoint.hpp"
#include "Global.hpp"

using namespace CoffeeEngine;
//using namespace CoffeeEngine::System;

int linux_main(int argc, char *argv[])
{
	//if( (g_pSystem = new ISystem()) != NULL)
	//{
	//	if(g_pSystem->Initialize())
	//		g_pSystem->Run();

	//	//Shutdown and release the memory.
	//	g_pSystem->Shutdown();
	//	delete g_pSystem;
	//}

	return 0;
}

#endif