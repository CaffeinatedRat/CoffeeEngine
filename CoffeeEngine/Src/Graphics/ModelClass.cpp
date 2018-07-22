//--------------------------------------------------------------------------------------
// Description: The base model class.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------


#include "Common.hpp"
#include "ModelClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
ModelClass::ModelClass(const BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == nullptr)
		throw NullArgumentException("ModelClass", "Constructor", "pBaseGraphicsClass");

	m_pGraphicsClass = pBaseGraphicsClass;
}

ModelClass::ModelClass(const ModelClass& otherClass) noexcept
	: m_enableAlphaBlending(otherClass.m_enableAlphaBlending),
	m_pGraphicsClass(otherClass.m_pGraphicsClass),
	m_shaders(otherClass.m_shaders)
{

}

ModelClass::ModelClass(ModelClass&& otherClass) noexcept
	: m_enableAlphaBlending(otherClass.m_enableAlphaBlending),
	m_pGraphicsClass(otherClass.m_pGraphicsClass),
	m_shaders(std::move(otherClass.m_shaders))
{
	otherClass.m_enableAlphaBlending = false;
	otherClass.m_pGraphicsClass = nullptr;
}

void ModelClass::AddShader(const IShader* pShader)
{
	assert(pShader);
	if (pShader != nullptr)
	{
		m_shaders.push_back(pShader);
	}
}

void ModelClass::AddShaders(std::vector<const IShader*>& pShaders)
{
	for (const IShader* pShader : pShaders) {
		if (pShader != nullptr) {
			m_shaders.push_back(pShader);
		}
	}
}
