//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#include "Graphics\BaseGraphicsClass.h"

#include "Common.h"
#include "Global.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

BaseGraphicsClass::BaseGraphicsClass()
{
	m_pSystem = NULL;
}

BaseGraphicsClass::BaseGraphicsClass(ISystem* pSystem)
{
	if(pSystem == NULL)
		throw NullArgumentException("ISystem is null.");

	m_pSystem = pSystem;
}

BaseGraphicsClass::BaseGraphicsClass(const BaseGraphicsClass& object)
{
	m_pSystem = object.m_pSystem;
}