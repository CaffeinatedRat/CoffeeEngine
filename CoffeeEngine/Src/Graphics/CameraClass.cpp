//--------------------------------------------------------------------------------------
// Description: The base camera class.
//
// Copyright (c) 2012-2017 Ken Anderson <caffeinatedrat@gmail.com>
// http://www.caffeinatedrat.com
//--------------------------------------------------------------------------------------

#include "Graphics/CameraClass.hpp"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////
CameraClass::CameraClass(const BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == nullptr)
		throw NullArgumentException("CameraClass", "Constructor", "pBaseGraphicsClass");

	m_pGraphicsClass = pBaseGraphicsClass;
}

CameraClass::CameraClass(const CameraClass& object)
{
	m_pGraphicsClass = object.m_pGraphicsClass;
}