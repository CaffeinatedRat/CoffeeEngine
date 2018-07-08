//--------------------------------------------------------------------------------------
// Description: The base shader class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _SHADER_CLASS_H_
#define _SHADER_CLASS_H_

#pragma once

#include "Common.hpp"
#include "BaseGraphicsClass.hpp"
#include "IShader.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class ShaderClass : public IShader
		{
		protected:
			const BaseGraphicsClass *m_pGraphicsClass = nullptr;

		public:
			ShaderClass() = delete;
			ShaderClass(const BaseGraphicsClass* pBaseGraphicsClass);
			ShaderClass(const ShaderClass& object);
			virtual ~ShaderClass() { };
		};
	};
};

#endif
