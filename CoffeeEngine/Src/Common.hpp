//--------------------------------------------------------------------------------------
// Description: Provides a common set of includes and definitions that are used globally that are not OS specific.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _COMMON_H_
#define _COMMON_H_

#pragma once

// C RunTime Header Files
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>

//STD libraries.
#include <string>
#include <vector>
#include <cassert>

// Exception classes.
#include "Exception.hpp"
#include "NullArgumentException.hpp"
#include "NotImplementedException.hpp"
#include "NotSupportedException.hpp"

using namespace CoffeeEngine::Exceptions;

//Define common data types that may not exist outside of the Windows Environment.
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

typedef unsigned int uint;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p != nullptr) { delete p; p = nullptr; }
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(p) if(p != nullptr) { delete[] p; p = nullptr; }
#endif

#endif
