//--------------------------------------------------------------------------------------
// Description: Manages the windows operating system.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once

#ifndef _WINDOWS_ENTRY_POINT_H_
#define _WINDOWS_ENTRY_POINT_H_

#include "stdafx.h"

//Forward declaration of the window's message handler.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Forward declaration.
int WinMain_ENTRY(HINSTANCE, HINSTANCE, LPTSTR, int);

#endif