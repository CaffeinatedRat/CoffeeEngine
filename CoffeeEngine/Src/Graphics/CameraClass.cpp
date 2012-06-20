//--------------------------------------------------------------------------------------
// Description: The base camera class.
//
// Copyright (c) 2012 Ken Anderson <caffeinatedrat@gmail.com>
//--------------------------------------------------------------------------------------

#include "Graphics\CameraClass.h"

using namespace CoffeeEngine;
using namespace CoffeeEngine::Graphics;

////////////////////////////////////////////////////////////
//
//                Constructors
// 
////////////////////////////////////////////////////////////

CameraClass::CameraClass()
{
	m_pGraphicsClass = NULL;
}

CameraClass::CameraClass(BaseGraphicsClass* pBaseGraphicsClass)
{
	if(pBaseGraphicsClass == NULL)
		throw NullArgumentException("BaseGraphicsClass is null.");

	m_pGraphicsClass = pBaseGraphicsClass;
}

CameraClass::CameraClass(const CameraClass& object)
{
	m_pGraphicsClass = object.m_pGraphicsClass;
}