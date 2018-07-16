// Description: Defines generic keyboard mappings.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _KEYBOARD_CLASS_H_
#define _KEYBOARD_CLASS_H_

namespace CoffeeEngine
{
	namespace Input
	{
		enum class KeyboardKeys : uint
		{
			Unknown,
			Escape,
			Enter,
			UpArrow,
			DownArrow,
			LeftArrow,
			RightArrow,
			Backspace,
			Space,
			Tab,
			Pause,
			Caps,
			Insert,
			Delete,
			Home,
			End,
			PageUp,
			PageDown,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			LeftShift,
			RightShift,
			Tilde,
			A = 0x41,
			B = 0x42,
			C = 0x43,
			D = 0x44,
			E = 0x45,
			F = 0x46,
			G = 0x47,
			H = 0x48,
			I = 0x49,
			J = 0x4A,
			K = 0x4B,
			L = 0x4C,
			M = 0x4D,
			N = 0x4E,
			O = 0x4F,
			P = 0x50,
			Q = 0x51,
			R = 0x52,
			S = 0x53,
			T = 0x54,
			U = 0x55,
			V = 0x56,
			W = 0x57,
			X = 0x58,
			Y = 0x59,
			Z = 0x5A		
		};
	}
}

#endif
