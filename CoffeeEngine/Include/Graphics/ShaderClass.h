//--------------------------------------------------------------------------------------
// Description: The base shader class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _SHADER_CLASS_H_
#define _SHADER_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Interfaces\IShader.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class ShaderClass : public IShader
		{
		protected:
			BaseGraphicsClass* m_pGraphicsClass;

		private:
			ShaderClass();

		public:
			
			ShaderClass(BaseGraphicsClass* pBaseGraphicsClass);
			ShaderClass(const ShaderClass& object);
			virtual ~ShaderClass() { };
		};
	};
};

#endif