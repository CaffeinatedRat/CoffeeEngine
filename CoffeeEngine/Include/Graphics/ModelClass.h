//--------------------------------------------------------------------------------------
// Description: The base model class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _MODEL_CLASS_H_
#define _MODEL_CLASS_H_

#pragma once

#include "Graphics/BaseGraphicsClass.h"
#include "Interfaces/IModel.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class ModelClass : public IModel
		{
		protected:
			const BaseGraphicsClass *m_pGraphicsClass = nullptr;

		public:		
			ModelClass() = delete;
			ModelClass(const BaseGraphicsClass* pBaseGraphicsClass);
			ModelClass(const ModelClass& object);
			virtual ~ModelClass() { };
		};
	};
};

#endif