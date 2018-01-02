//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.h"
#include "Graphics/BaseGraphicsClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
BaseGraphicsClass::BaseGraphicsClass(ISystem* pSystem, std::string sGraphicsLibraryName)
{
	if(pSystem == nullptr)
		throw NullArgumentException("BaseGraphicsClass", "Constructor", "pSystem");

	m_pSystem = pSystem;
	m_sGraphicsLibraryName = sGraphicsLibraryName;
}

BaseGraphicsClass::BaseGraphicsClass(const BaseGraphicsClass& object) noexcept
{
	m_pSystem = object.m_pSystem;
	m_sGraphicsLibraryName = object.m_sGraphicsLibraryName;
}