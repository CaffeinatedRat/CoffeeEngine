//--------------------------------------------------------------------------------------
// Description: The base model class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#ifndef _MODEL_CLASS_H_
#define _MODEL_CLASS_H_

#pragma once

#include "BaseGraphicsClass.hpp"
#include "IModel.hpp"

using namespace CoffeeEngine::Interfaces;

namespace CoffeeEngine
{
	namespace Graphics
	{
		class ModelClass : public IModel
		{
		public:		
			ModelClass() = delete;
			ModelClass(const BaseGraphicsClass* pBaseGraphicsClass);
			ModelClass(const ModelClass& otherClass) noexcept;
			ModelClass(ModelClass&& otherClass) noexcept;
			virtual ~ModelClass() { };

			ModelClass& operator=(const ModelClass&) = default;
			ModelClass& operator=(ModelClass&&) = default;

			void AddShader(const IShader* pShader);
			void AddShaders(std::vector<const IShader*>& pShader);

			////////////////////////////////////////////////////////////
			//
			//                Member Vars
			// 
			////////////////////////////////////////////////////////////

		protected:
			const BaseGraphicsClass *m_pGraphicsClass = nullptr;
			std::vector<const IShader*> m_shaders;

			bool m_enableAlphaBlending = false;

		};
	};
};

#endif
