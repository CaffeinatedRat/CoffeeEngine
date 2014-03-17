//--------------------------------------------------------------------------------------
// Description: The base model class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Graphics/ModelClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

ModelClass::ModelClass()
{
	m_pGraphicsClass = NULL;
}

ModelClass::ModelClass(BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == NULL)
		throw NullArgumentException("ModelClass", "Constructor", "pBaseGraphicsClass");

	m_pGraphicsClass = pBaseGraphicsClass;
}

ModelClass::ModelClass(const ModelClass& object)
{
	m_pGraphicsClass = object.m_pGraphicsClass;
}