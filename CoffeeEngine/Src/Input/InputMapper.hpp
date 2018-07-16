// Description: Defines generic keyboard mappings.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _INPUTMAPPER_CLASS_H_
#define _INPUTMAPPER_CLASS_H_

#include "Keyboard.hpp"

namespace CoffeeEngine
{
	namespace Input
	{
		class InputMapper
		{
		public:
			InputMapper() = default;
			InputMapper(const InputMapper&) = delete;
			virtual ~InputMapper() noexcept;

		private:

		};
	}
}

#endif
