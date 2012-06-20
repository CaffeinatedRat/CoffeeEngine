//--------------------------------------------------------------------------------------
// Description: The base shader class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#include "Graphics\ShaderClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

ShaderClass::ShaderClass()
{
	m_pGraphicsClass = NULL;
}

ShaderClass::ShaderClass(BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == NULL)
		throw NullArgumentException("BaseGraphicsClass is null.");

	m_pGraphicsClass = pBaseGraphicsClass;
}

ShaderClass::ShaderClass(const ShaderClass& object)
{
	m_pGraphicsClass = object.m_pGraphicsClass;
}