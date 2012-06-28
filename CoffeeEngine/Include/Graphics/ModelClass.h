//--------------------------------------------------------------------------------------
// Description: The base model class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _MODEL_CLASS_H_
#define _MODEL_CLASS_H_

#include "Common.h"
#include "Graphics\BaseGraphicsClass.h"
#include "Interfaces\IModel.h"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class ModelClass : public IModel
		{
		protected:
			BaseGraphicsClass* m_pGraphicsClass;

		private:
			ModelClass();

		public:
			
			ModelClass(BaseGraphicsClass* pBaseGraphicsClass);
			ModelClass(const ModelClass& object);
			virtual ~ModelClass() { };
		};
	};
};

#endif