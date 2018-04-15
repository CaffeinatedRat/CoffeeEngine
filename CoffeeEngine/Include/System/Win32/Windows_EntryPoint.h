//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifdef _WIN32

#ifndef _WINDOWS_ENTRY_POINT_H_
#define _WINDOWS_ENTRY_POINT_H_

#pragma once

#include "stdafx.h"

//Forward declaration of the window's message handler.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Forward declaration.
int WinMain_ENTRY(HINSTANCE, HINSTANCE, LPTSTR, int);

#endif

#endif