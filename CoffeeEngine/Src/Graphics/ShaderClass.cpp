//--------------------------------------------------------------------------------------
// Description: The base shader class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "ShaderClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
ShaderClass::ShaderClass(const BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == nullptr)
		throw NullArgumentException("ShaderClass", "Constructor", "pBaseGraphicsClass");

	m_pGraphicsClass = pBaseGraphicsClass;
}

ShaderClass::ShaderClass(const ShaderClass& object)
{
	m_pGraphicsClass = object.m_pGraphicsClass;
}