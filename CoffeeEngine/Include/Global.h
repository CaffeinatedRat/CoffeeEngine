//--------------------------------------------------------------------------------------
// Description: Provides a global set of variables that exist through out the lifetime of the application.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Interfaces\ISystem.h"

using namespace CoffeeEngine::Interfaces;

extern "C" ISystem* g_pSystem;

#endif