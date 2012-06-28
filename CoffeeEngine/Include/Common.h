//--------------------------------------------------------------------------------------
// Description: Provides a common set of includes and definitions that are used globally that are not OS specific.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string>
#include <vector>

// Exception classes.
#include "Exceptions\Exception.h"
#include "Exceptions\NullArgumentException.h"
#include "Exceptions\NotImplementedException.h"

using namespace CoffeeEngine::Exceptions;

#ifndef NULL
#define NULL = 0
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef DWORD
#define DWORD unsigned long
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p != NULL) { delete p; p = NULL; }
#endif

#ifndef SAFE_ARRAY_DELETE
#define SAFE_ARRAY_DELETE(p) if(p != NULL) { delete[] p; p = NULL; }
#endif

#endif