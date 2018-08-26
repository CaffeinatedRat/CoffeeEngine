//--------------------------------------------------------------------------------------
// Description: The base graphics class.  Used to provide a a foundation for all the graphics classes that should be created.
//
// Copyright (c) 2012-2018 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Common.hpp"
#include "BaseGraphicsClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;
using LogLevelType = CoffeeEngine::Utility::Logging::LogLevelType;

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
	m_graphicsLibraryName = sGraphicsLibraryName;
}

BaseGraphicsClass::BaseGraphicsClass(const BaseGraphicsClass& object) noexcept
	: m_pSystem(object.m_pSystem),
	m_displayReady(object.m_displayReady),
	m_graphicsLibraryName(object.m_graphicsLibraryName),
	m_graphicsPresentationProperties(object.m_graphicsPresentationProperties)
{
}

BaseGraphicsClass::BaseGraphicsClass(BaseGraphicsClass&& object) noexcept
	: m_pSystem(object.m_pSystem),
	m_displayReady(object.m_displayReady),
	m_graphicsLibraryName(std::move(object.m_graphicsLibraryName)),
	m_graphicsPresentationProperties(std::move(object.m_graphicsPresentationProperties))
{
	object.m_pSystem = nullptr;
	object.m_displayReady = false;
	object.m_graphicsLibraryName = std::string();
	object.m_displayReady = false;
	object.m_graphicsPresentationProperties = GRAPHICS_PRESENTATION_PROPERTIES();
}

bool BaseGraphicsClass::Initialize(const GRAPHICS_PRESENTATION_PROPERTIES& graphicsInitParameters)
{
	std::stringstream message;
	message << "[BaseGraphicsClass::Initialize] Using Coordinate System: " << COORDINATE_SYSTEM;
	m_pSystem->WriteToLog(message, LogLevelType::Informational);

	m_graphicsPresentationProperties = graphicsInitParameters;
	return true;
}