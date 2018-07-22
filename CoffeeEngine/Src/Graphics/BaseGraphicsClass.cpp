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

	m_bFullScreen = object.m_bFullScreen;
	m_bDisplayReady = object.m_bDisplayReady;
	m_bVsyncEnabled = object.m_bVsyncEnabled;
	m_nScreenWidth = object.m_nScreenWidth;
	m_nScreenHeight = object.m_nScreenHeight;
	m_videoCardMemory = object.m_videoCardMemory;
	m_nNumOfModes = object.m_nNumOfModes;
	m_version = object.m_version;
	m_ScreenDepth = object.m_ScreenDepth;
	m_ScreenNear = object.m_ScreenNear;


}

BaseGraphicsClass::BaseGraphicsClass(BaseGraphicsClass&& object) noexcept
{
	m_pSystem = object.m_pSystem;
	m_sGraphicsLibraryName = std::move(object.m_sGraphicsLibraryName);

	m_bFullScreen = object.m_bFullScreen;
	m_bDisplayReady = object.m_bDisplayReady;
	m_bVsyncEnabled = object.m_bVsyncEnabled;
	m_nScreenWidth = object.m_nScreenWidth;
	m_nScreenHeight = object.m_nScreenHeight;
	m_videoCardMemory = object.m_videoCardMemory;
	m_nNumOfModes = object.m_nNumOfModes;
	m_version = std::move(object.m_version);
	m_ScreenDepth = object.m_ScreenDepth;
	m_ScreenNear = object.m_ScreenNear;

	object.m_bFullScreen = object.m_bVsyncEnabled = false;
	object.m_bDisplayReady = false;
	object.m_nScreenWidth = object.m_nScreenHeight = 0;
	object.m_videoCardMemory = 0;
	object.m_nNumOfModes = 0;
	object.m_ScreenDepth = 0.0f;
	object.m_ScreenNear = 0.0f;
}

bool BaseGraphicsClass::Initialize(const CoffeeEngine::Graphics::GRAPHICS_INITIALIZATION_PARAMETERS& graphicsInitParameters)
{
	m_nScreenWidth = graphicsInitParameters.nScreenWidth;
	m_nScreenHeight = graphicsInitParameters.nScreenHeight;
	m_bVsyncEnabled = graphicsInitParameters.bVsync;
	m_bFullScreen = graphicsInitParameters.bFullscreen;
	m_version.nMajor = graphicsInitParameters.version.nMajor;
	m_version.nMinor = graphicsInitParameters.version.nMinor;
	m_ScreenDepth = graphicsInitParameters.fScreenDepth;
	m_ScreenNear = graphicsInitParameters.fScreenNear;

	return true;
}