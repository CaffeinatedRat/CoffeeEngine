//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
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
	m_sGraphicsLibraryName = "Undefined";
}

BaseGraphicsClass::BaseGraphicsClass(ISystem* pSystem, std::string sGraphicsLibraryName)
{
	if(pSystem == NULL)
		throw NullArgumentException("BaseGraphicsClass", "Constructor", "pSystem");

	m_pSystem = pSystem;
	m_sGraphicsLibraryName = sGraphicsLibraryName;
}

BaseGraphicsClass::BaseGraphicsClass(const BaseGraphicsClass& object)
{
	m_pSystem = object.m_pSystem;
	m_sGraphicsLibraryName = object.m_sGraphicsLibraryName;
}